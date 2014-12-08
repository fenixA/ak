#include <iostream>
#include <string>
#include "filters.h" // StringSink
#include "hex.h" // HexEncoder
#include "aes.h" // AES
#include "modes.h" // ECB_Mode
#include "sha.h"
#include "base64.h"
#include "files.h" // FileSink
#include "osrng.h" // BlockingRNG
#include "integer.h" // Integer
#include "nbtheory.h" // RabinMillerTest
#include "BlumBlumShubGenerator.h"

using namespace std;
using namespace CryptoPP;

void DataFlowExercise() {
	cout << endl
	     << "Data Flow Exercise:" << endl
	     << "===================" << endl << endl;

	string src = "Kryptografie macht Spass!!!";
	string dst;
	StringSink* sink = new StringSink(dst);
	HexEncoder* encoder = new HexEncoder(sink);
	StringSource(src, true, encoder);
	// StringSource(src, true,	new HexEncoder(	new StringSink(dst)	)	);
	cout << "--DataFlowExercise 2A--" << endl << dst << endl;


	string src2 = "4963682062696E2065696E20537472696E6720696E204865786164657A696D616C6B6F64696572756E6721";
	string dst2;
	StringSink* sink2 = new StringSink(dst2);
	HexDecoder* decoder2 = new HexDecoder(sink2);
	StringSource(src2, true, decoder2);

	cout << "--DataFlowExercise 2B--" << endl << dst2 << endl;


	string dst3;
	StringSink* sink3 = new StringSink(dst3);
	Base64Decoder* decoder3 = new Base64Decoder(sink3);
	FileSource("../data/base64data.txt", true, decoder3);

	cout << "--DataFlowExercise 2C--" << endl << dst3 << endl;

}

void EncryptionExercise() {

	string plain_text = "Streng geheime Botschaft";
	string plain_text2;
	string encoded_key = "08a8cbfe7a3d1262c8abc3d1197dfefe";
	string cipher_text;

	ECB_Mode<AES>::Encryption aes_enc;
	ECB_Mode<AES>::Decryption aes_dec;

	byte key[16];

	StringSource(encoded_key, true,
			new HexDecoder(
					new ArraySink(key, 16)
			)
	);

	aes_enc.SetKey(key, sizeof(key));
	aes_dec.SetKey(key, sizeof(key));

// Exerecize 2 A
	try
	{
		StringSource(plain_text, true,
			new StreamTransformationFilter(aes_enc,
					new HexEncoder(
							new StringSink(cipher_text)
					)
			)
		);
	}
	catch (const Exception& e)
	{
		cerr << e.what() << endl;
		assert(false);
	}

	cout << "--EncryptionExercise 3A--" << endl << cipher_text << endl;

// Exercise 3 B

	try
	{
		StringSource(cipher_text, true,
			new HexDecoder(
				new StreamTransformationFilter(aes_dec,
					new StringSink(plain_text2)
				)
			)
		);
	}
	catch (const Exception& e)
	{
		cerr << e.what() << endl;
		assert(false);
	}

	cout << "--EncryptionExercise 3B--" << endl << plain_text2 << endl;


// Exercise  2 C

	try
	{
		string keyC_enc = "47656865696D65725363686CC3BC7373";
		string vectorC_enc = "496E697469616C6973696572756E6773";
		string plain_textC;
		byte keyC[16];
		byte vectorC[16];

		CTR_Mode< AES >::Decryption ctr_dec;



			StringSource(keyC_enc, true,
					new HexDecoder(
							new ArraySink(keyC, 16)
							)
					);

			StringSource(vectorC_enc, true,
					new HexDecoder(
							new ArraySink(vectorC, 16)
							)
						);

		ctr_dec.SetKeyWithIV( keyC, sizeof(keyC), vectorC );

		FileSource( "../data/aescipher.txt", true,
			new Base64Decoder(
		        new StreamTransformationFilter( ctr_dec,
		            new StringSink( plain_textC )
		        )
			)
		);

		    cout << "--EncryptionExercise 3C-- " << endl << plain_textC << endl;
	}
	catch (const Exception& e)
	{
		cerr << e.what() << endl;
		assert(false);
	}
}

void HashExercise() {

	string message = "Kryptografie macht immer noch Spass!!!";
	string digest;
	SHA256 hash;
	word32 flags = HashVerificationFilter::HASH_AT_BEGIN | HashVerificationFilter::PUT_RESULT;
	bool result;

	StringSource(message, true,
			new HashFilter(hash,
				new StringSink(digest)
				)
			);

	hash.Restart();
	StringSource(digest + message, true,
			new HashVerificationFilter(hash,
				new ArraySink((byte*)&result, sizeof(result)),flags
					)
		);

	cout << "--Hash 4A--" << endl << "result :" << result << endl;

//Hash B
	string message2 = "macht Kryptografie immer noch Spass";
	hash.Restart();
		StringSource(digest + message2, true,
				new HashVerificationFilter(hash,
					new ArraySink((byte*)&result, sizeof(result)),flags
						)
			);
	cout << "--Hash 4B changed message--" << endl << "result :"
			<< result << endl;

	digest += 1;


		hash.Restart();
			StringSource(digest + message, true,
					new HashVerificationFilter(hash,
						new ArraySink((byte*)&result, sizeof(result)),flags
							)
				);
		cout << "--Hash 4B changed digest--" << endl << "result :"
				<< result << endl;
//Hash C
		cout << "word32 flags = HashVerificationFilter::HASH_AT_END" << endl;

}

Integer modexp(const Integer& a, const Integer& b, const Integer& n) {
	//Integer c("0");
	Integer d("1");
	int k = b.BitCount();

	for(int i = k; i >= 0; i--)
	{
		//c *= 2;
		d = (d * d) % n;

		if( b.GetBit(i) == 1)
		{
			//c += 1;
			d = (d * a) % n;
		}
	}
	return d;
}

void IntegerExercise() {
	Integer a("371");
	Integer b("18961551");
	Integer n("2371");

	Integer value = modexp(a,b,n);
	Integer value2 = a_exp_b_mod_c(a,b,n);
	Integer value3 = modexp(58788,(95957-1)/2,95957);




	cout << endl
		 << "IntegerExercise:" << endl
		 << "================" << endl
		 << "b: " << value << endl
		 << "Test: " << value2 << endl
		 << "c: " << value3 << endl;



}

void RNGExercise() {
	Integer q = 1476222059624949757818143837507324048590620075519516306265283;
	Integer p = 1252910265243849922375596598575099209083498535192739493227403;
	Integer n = p * q;
	Integer s = 42;
	Integer values [20];
	BlumBlumShubGenerator t(n,s);

	cout << "RNGExercise C:" << endl
	     << "============" << endl;

	for(int i = 0; i < 20; i++)
	{
		values[i] = t.getBit();
		 cout << values[i];
	}
	cout << endl;

	cout << "RNGExercise D:" << endl
		     << "============" << endl;
		int valueD = t.getByte();
		cout << valueD << endl;

	cout << "RNGExercise F:" << endl
			<< "============" << endl;
	int size = 100;
	byte buffer [size];
	t.getBlock(buffer, size);

	for(int i = 0; i < size; i++)
	{
		cout << (unsigned int ) buffer[i] << "|";
	}



	cout << endl << "RNGExercise H:" << endl
			<< "============" << endl;
	int size2 = 200;
	byte buffer2[size2];
	Integer h = t.getInteger(size2);
	cout << h << endl;

	cout << endl << "RNGExercise J:" << endl
				<< "============" << endl;

	Integer j = Integer::Power2(30);
	Integer j2 = t.getInteger(j);
	cout << j2 << endl;

}

int main() {
	//DataFlowExercise();
	//EncryptionExercise();
	//HashExercise();
	//IntegerExercise();
	//RNGExercise();

	return 0;
}
