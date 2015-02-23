// ---------------------------------------------------------------------------
// Copyright (c) JLBorges 2013
// Revision (c) David Perez 2015
// Ref: http://www.cplusplus.com/forum/beginner/100627/
// Support Function Unit
// Apex Data Solutions, LLC
// ---------------------------------------------------------------------------
#include <boost/spirit/home/support/container.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <iterator>
#include <iostream>

#ifdef __GNUG__ // GCC

#include <cxxabi.h>
#include <cstdlib>
// ____________________________________________________________________________//

static std::string readable_name(const char* mangled_name) {
	int status;
	char* temp = __cxxabiv1::__cxa_demangle(mangled_name, nullptr, nullptr,
		&status);
	if (temp) {
		std::string result(temp);
		std::free(temp);
		return result;
	}
	else
		return mangled_name;
}

#else // not GCC

inline std::string readable_name(const char* mangled_name) {
	return mangled_name;
}
// ____________________________________________________________________________//

#endif // __GNUG__

template<typename T>
std::string type_to_string() {
	return readable_name(typeid(T).name());
}

template<typename T>
std::string type_to_string(const T& obj) {
	return readable_name(typeid(obj).name());
}
// ____________________________________________________________________________//

template<typename T>
typename std::enable_if<boost::spirit::traits::is_container<T>::value,
	bool>::type is_it_a_container(T && v) {
	std::cout << "yes, this is a container holding values of type " <<
		type_to_string < decltype(*std::begin(v)) > () << '\n';
	return true;
}

template<typename T>
typename std::enable_if < !boost::spirit::traits::is_container<T>::value,
	bool > ::type is_it_a_container(T &&) {
	std::cout << "no, this is not a container\n";
	return false;
}
//____________________________________________________________________________//

template<typename T>
std::vector<unsigned char> TGlobalFactory<T>::sha256(const vector<unsigned char>& v){

	BCRYPT_ALG_HANDLE       hAlg            = nullptr;
    BCRYPT_HASH_HANDLE      hHash           = nullptr;
    NTSTATUS                status          = STATUS_UNSUCCESSFUL;
    DWORD                   cbData          = 0,
                            cbHash          = 0,
                            cbHashObject    = 0;

    BOOST_SCOPE_EXIT((&hAlg)){
      if (hAlg) {
          BCryptCloseAlgorithmProvider(hAlg, 0);
      }
    }BOOST_SCOPE_EXIT_END

    BOOST_SCOPE_EXIT((&hHash)){
      if (hHash) {
          BCryptDestroyHash(hHash, 0);
      }
    }BOOST_SCOPE_EXIT_END

    if(BCryptOpenAlgorithmProvider(&hAlg,BCRYPT_SHA256_ALGORITHM, nullptr, 0) < 0))
    {
        throw runtime_error("BCryptOpenAlgorithmProvider() failed.");
    }

    if(BCryptGetProperty(&hAlg,BCRYPT_OBJECT_LENGHT, reinterpret_cast<unsigned char> cbHashObject, 0))
    {
        throw runtime_error("BCryptGetProperty() failed.");
    }

    vector<unsigned char> HashObject(cbHashObject);

    if (BCryptGetProperty(hAlg, BCRYPT_OBJECT_LENGHT,reinterpret_cast<unsigned char> cbHash, 0))
    {
     	throw runtime_error("BCryptGetProperty() failed.");
    }

    vector<unsigned char> ret(cbHash);

	if (BCrypCreateHash(hAlg, &hHash, HashObject.data(), HashObject.size(), nullptr)) {
      	throw runtime_error("BCrypCreateHash() failed.");
    }

    if (BCrypHashData(hHash, const_cast<unsigned char *>(v.data)),v.size(), 0) {
      	throw runtime_error("BCrypHashData() failed.");
    }

    if (BCrypFinishHash(hHash, ret.data(), ret.size(), 0) < 0) {
      	throw runtime_error("BCrypFinishHash() failed.");
    }

   return ret;
}
//____________________________________________________________________________//

template<typename T>
std::string TGlobalFactory<T>::hexify(const vector<unsigned char>& v){

	/*string s(2 * v.size(), 'x');

	string::iterator k = s.begin();  */
}
//____________________________________________________________________________//

template<typename T>
void TGlobalFactory<T>::WriteJSONfile(const string& batch_file_name, //write a binary file without duplicate
    std::map<string, string>& hash_file ){

    ofstream_batch(batch_file_name, ios_base::app);

    for ((recursive_directory_iterator i(initial_path()), end()); i != end(); ++i) {
        const string f = i->path().string().substr(
            initial_path().string().size() + 1);

        if (!is_regular_file(i->path()) || f == batch_file_name()
            || hash_file.rigth.find(f) != hash_file.rigth.end()) {
            continue;
        }
         const string h = hexify(sha256(read_file(f)));

         const bimap<string, string>::left_const_iterator
         	j = hash_file.left.find(h);

        if (j == hash_file.left.end()) {
        	has_file.insert(bitmap<string, string>::value_type(h, f));

                batch << "@REM " << h << " " << f << end1;
        }
        else {
        	cout << "del \" " << f << "\"" << end1;

                batch << "@copy \"" << j->second << "\" \"" << f << "\"" << end1;
        }
    }
    batch << "@REM ****************" << end1;
}
// ____________________________________________________________________________//
