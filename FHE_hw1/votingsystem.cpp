//#define MAX_CANDIDATE 4
//#include "seal/seal.h"
//#include <iostream>
//
//using namespace seal;
//using namespace std;
//int main() {
//
//   cout << "��ǥ �ý��� ����." << endl;
//
//   EncryptionParameters parms(scheme_type::bfv);            // bfv ������ȣ�� �� ���̴� �Ķ���͸� �غ��ض�
//   size_t poly_modulus_degree = 4096;                       // �� ��ȣ���� �ִ� 4096�������� ������ �޽����� ��ȣȰ �� �ִ�. 2�� ���������� ���� ����, �������� ���� ���� ����
//
//   // �� ������� ��Ÿ �Ķ���� ����
//   parms.set_poly_modulus_degree(poly_modulus_degree);
//   parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));         // ����Ʈ�� 4096�� �µ��� modulus ũ�� �����ش�. modulus�� ��ȣ���� �̷�� �� ���ڰ� ��� ���� ���� ���� ���ϴ°��� �ǹ�
//   parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 20));       // 20�� ���� ���� 20��Ʈ (�� 2^20 ũ����) �������� �ǹ�; �� ������ �̷���� �� ���� ���� ����� 2^20�� ���� �ʴ� �� ���� ������ �� ����ȴ�. �׷��� ���� ��� 2^20 ũ���� ������ ���� �������� ��µ�
//
//   SEALContext context(parms);     // �Ķ���Ϳ� �°� ���� �⺻ context ���� (������ �ʿ� ����)
//
//   KeyGenerator keygen(context);   // Ű ����
//   SecretKey secret_key = keygen.secret_key();  // ���Ű ����
//   PublicKey public_key;
//   keygen.create_public_key(public_key);       // ����Ű ����
//
//   Encryptor encryptor(context, public_key);   // ��ȣȭ�� ���� ��ü ���� 
//   Evaluator evaluator(context);               // ��ȣ���� ���� ������ ���� ��ü ����
//   Decryptor decryptor(context, secret_key);   // ��ȣȭ�� ���� ��ü ����
//   BatchEncoder encoder(context);              // ���� ���� �� ��ȣ���� �ֱ� ���� ���ڴ� ��ü ����
//   size_t slot_count = encoder.slot_count();   // �� ��ȣ���� � ������ ���� ���� �� �ִ°��� slot_count ������ ���� 
//   Ciphertext total_votes;
//   encryptor.encrypt(Plaintext("0"), total_votes); // ��ü ��ǥ ��� �ʱ�ȭ
//
//   cout << "��ȣȭ/��ȣȭ �غ� �Ϸ�. " << endl;
//   
//   while (true)
//   {
//	   vector<uint64_t> plain_vector(slot_count, 0ULL);    // slot_count ������ ���Ҹ� ���ϴ� 0���� �̷���� ���� ����
//	   int voted_candidate = 0;
//	   cout << "��ǥ�� �ĺ� ���� 1.����ȯ 2.���ڿ� 3.������ 4.��ȣ�� (���� �� 0 �Է�) : ";
//	   cin >> voted_candidate;
//	   if (voted_candidate == 0) { cout << "��ǥ�� �����մϴ�." << endl; break; }
//	   else if (voted_candidate > MAX_CANDIDATE) { cout << "�ùٸ��� ���� �ĺ��Դϴ�." << endl;  }
//	   else
//	   {
//		   plain_vector[voted_candidate - 1]++;
//		   // ���� �����Ͽ� ���ڵ� (�� �� �޽��� ���͸� ��ȣȭ�ϱ� ���ؼ� ���¸� �����ϴ� ���̶� �����Ͻø� �˴ϴ�. ��Ȯ���� ���׽����� ����)
//		   Plaintext plain;
//		   encoder.encode(plain_vector, plain);
//
//		   // ��ȣ�� ���� �� encrypted ��� ��ȣ���� �� ���� ��ȣȭ�� ����� ����
//		   Ciphertext encrypted;
//		   encryptor.encrypt(plain, encrypted);
//		   cout << "��ȣȭ �Ϸ�." << endl;
//
//		   if (total_votes.size() == 0) {  // ù ��ǥ�� ��� �ʱ�ȭ
//			   total_votes = encrypted;  // ù ��ǥ ����
//		   }
//		   else {  // ���� ��ǥ�� ���� ���� ����
//			   evaluator.add_inplace(total_votes, encrypted);
//		   }
//	   }
//   }
//   system("cls");
//   // ��ȣȭ ����� ������ ���� ����
//   Plaintext plain_result;
//   decryptor.decrypt(total_votes, plain_result);
//
//   // ��ȣȭ�� ���� �ٽ� �޽��� ���ͷ� ���ڵ�, ���� ��� ���
//   vector<uint64_t> result_vector;
//   encoder.decode(plain_result, result_vector);
//   cout << "��ȣȭ �Ϸ�" << endl;
//
//   cout << "Result: " << endl;
//      cout << "��ǥ ��� : ";
//	  for (int i = 0; i < MAX_CANDIDATE; i++) { cout << result_vector[i] << " "; }
//   cout << endl;
//
//   return 0;
//}
//
//
//
//
