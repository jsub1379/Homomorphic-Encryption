//#define MAX_CANDIDATE 4
//#include "seal/seal.h"
//#include <iostream>
//
//using namespace seal;
//using namespace std;
//int main() {
//
//   cout << "투표 시스템 시작." << endl;
//
//   EncryptionParameters parms(scheme_type::bfv);            // bfv 동형암호를 쓸 것이니 파라미터를 준비해라
//   size_t poly_modulus_degree = 4096;                       // 한 암호문에 최대 4096개까지의 독립된 메시지를 암호활 수 있다. 2의 지수승으로 조정 가능, 작을수록 빠른 연산 제공
//
//   // 위 설정대로 기타 파라미터 설정
//   parms.set_poly_modulus_degree(poly_modulus_degree);
//   parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));         // 디폴트로 4096에 맞도록 modulus 크기 정해준다. modulus는 암호문을 이루는 각 숫자가 어느 모듈로 정수 값을 지니는가를 의미
//   parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 20));       // 20은 평문이 모듈로 20비트 (약 2^20 크기의) 정수임을 의미; 즉 정수로 이루어진 평문 간의 연산 결과가 2^20을 넘지 않는 한 정수 연산이 잘 수행된다. 그렇지 않을 경우 2^20 크기의 정수로 나눈 나머지가 출력됨
//
//   SEALContext context(parms);     // 파라미터에 맞게 여러 기본 context 설정 (수정할 필요 없음)
//
//   KeyGenerator keygen(context);   // 키 생성
//   SecretKey secret_key = keygen.secret_key();  // 비밀키 생성
//   PublicKey public_key;
//   keygen.create_public_key(public_key);       // 공개키 생성
//
//   Encryptor encryptor(context, public_key);   // 암호화를 위한 객체 생성 
//   Evaluator evaluator(context);               // 암호문에 대한 연산을 위한 객체 생성
//   Decryptor decryptor(context, secret_key);   // 복호화를 위한 객체 생성
//   BatchEncoder encoder(context);              // 여러 평문을 한 암호문에 넣기 위한 인코더 객체 생성
//   size_t slot_count = encoder.slot_count();   // 한 암호문에 몇개 까지의 평문을 넣을 수 있는가를 slot_count 변수에 저장 
//   Ciphertext total_votes;
//   encryptor.encrypt(Plaintext("0"), total_votes); // 전체 투표 결과 초기화
//
//   cout << "암호화/복호화 준비 완료. " << endl;
//   
//   while (true)
//   {
//	   vector<uint64_t> plain_vector(slot_count, 0ULL);    // slot_count 개수의 원소를 지니는 0으로 이루어진 벡터 생성
//	   int voted_candidate = 0;
//	   cout << "투표할 후보 선택 1.김재환 2.구자욱 3.최형우 4.손호영 (종료 시 0 입력) : ";
//	   cin >> voted_candidate;
//	   if (voted_candidate == 0) { cout << "투표를 종료합니다." << endl; break; }
//	   else if (voted_candidate > MAX_CANDIDATE) { cout << "올바르지 않은 후보입니다." << endl;  }
//	   else
//	   {
//		   plain_vector[voted_candidate - 1]++;
//		   // 평문을 생성하여 인코딩 (즉 평문 메시지 벡터를 암호화하기 위해서 형태를 변경하는 것이라 이해하시면 됩니다. 정확히는 다항식으로 변경)
//		   Plaintext plain;
//		   encoder.encode(plain_vector, plain);
//
//		   // 암호문 생성 후 encrypted 라는 암호문에 위 평문을 암호화한 결과를 저장
//		   Ciphertext encrypted;
//		   encryptor.encrypt(plain, encrypted);
//		   cout << "암호화 완료." << endl;
//
//		   if (total_votes.size() == 0) {  // 첫 투표인 경우 초기화
//			   total_votes = encrypted;  // 첫 투표 복사
//		   }
//		   else {  // 이후 투표는 기존 값에 더함
//			   evaluator.add_inplace(total_votes, encrypted);
//		   }
//	   }
//   }
//   system("cls");
//   // 복호화 결과를 저장할 곳을 생성
//   Plaintext plain_result;
//   decryptor.decrypt(total_votes, plain_result);
//
//   // 복호화한 평문을 다시 메시지 벡터로 디코딩, 이후 결과 출력
//   vector<uint64_t> result_vector;
//   encoder.decode(plain_result, result_vector);
//   cout << "복호화 완료" << endl;
//
//   cout << "Result: " << endl;
//      cout << "투표 결과 : ";
//	  for (int i = 0; i < MAX_CANDIDATE; i++) { cout << result_vector[i] << " "; }
//   cout << endl;
//
//   return 0;
//}
//
//
//
//
