#include <iostream>
#include <cstring>

#include "common_tool.h"


static void ERR(const char* string);
using namespace std;
static std::string sign(const char *private_key,const std::string &content) {
    BIO *bufio = NULL;
    RSA *rsa = NULL;
    EVP_PKEY *evpKey = NULL;
    bool verify = false;
    EVP_MD_CTX ctx ;
    int result = 0;
    unsigned int size = 0;
    char *sign = NULL;
    std::string signStr = "";

   /* bufio = BIO_new_mem_buf((void*)private_key, -1);
    if (bufio == NULL) {
    	ERR("BIO_new_mem_buf failed");
    	goto safe_exit;
    }*/
    bufio = BIO_new(BIO_s_file());
    // BIO_read_filename(bufio, "rsa_private_key_pkcs8.pem");
    BIO_read_filename(bufio, "rsa_private_key.pem"); // 20210811fhp
   
    rsa = PEM_read_bio_RSAPrivateKey(bufio, NULL, NULL, NULL);
    if (rsa == NULL) {
        ERR("PEM_read_bio_RSAPrivateKey failed");
        goto safe_exit;
    }
    
    evpKey = EVP_PKEY_new();
    if (evpKey == NULL) {
        ERR("EVP_PKEY_new failed");
        goto safe_exit;
    }
    
    if ((result = EVP_PKEY_set1_RSA(evpKey, rsa)) != 1) {
        ERR("EVP_PKEY_set1_RSA failed");
        goto safe_exit;
    }
    cout<<"L45 success"<<endl;
    EVP_MD_CTX_init(&ctx);
    cout<<"L47 success"<<endl;
    if (result == 1 && (result = EVP_SignInit_ex(&ctx, EVP_md5(), NULL)) != 1) {
        ERR("EVP_SignInit_ex failed");
    }
    
    if (result == 1 && (result = EVP_SignUpdate(&ctx, content.c_str(), content.size())) != 1) {
        ERR("EVP_SignUpdate failed");
    }
    
    size = EVP_PKEY_size(evpKey);
    sign = (char*)malloc(size+1);   // 20210811fhp
    memset(sign, 0, size+1);

    if (result == 1 && (result = EVP_SignFinal(&ctx, (unsigned char*)sign, &size, evpKey)) != 1) {
        ERR("EVP_SignFinal failed");
    }

    if (result == 1) {
        verify = true;
    } else {
        ERR("verify failed");
    }

    signStr = base64_encode((const unsigned char*)sign, size);
    // EVP_MD_CTX_cleanup(&ctx);
    EVP_MD_CTX_destroy(&ctx);   // 20210811fhp
    free(sign);

    safe_exit:
    if (rsa != NULL) {
        RSA_free(rsa);
        rsa = NULL;
    }

    if (evpKey != NULL) {
        EVP_PKEY_free(evpKey);
        evpKey = NULL;
    }

    if (bufio != NULL) {
        BIO_free_all(bufio);
        bufio = NULL;
    }

    return signStr;
    //return sign;
}

static void ERR(const char* string) {
    std::cout<<"error  "<<string<<std::endl;
}

int main() {
    // https://blog.csdn.net/m0_37847176/article/details/82682293
    std::cout << "Hello, World!" << std::endl;
    std::string message="shadkfkaslkdfj";
    std::string prikey="";
    std::string signtxt=sign("",message);
    std::cout<<signtxt<<std::endl;

    BIO *bufio = NULL;
    RSA *rsa = NULL;
    bufio = BIO_new(BIO_s_file());
    BIO_read_filename(bufio, "rsa_public_key.pem");
    rsa = PEM_read_bio_RSA_PUBKEY(bufio, NULL, NULL, NULL);
    common_tool ct;
    std::cout<<ct.verify_rsa(rsa,message,signtxt)<<std::endl;

    return 0;
}
