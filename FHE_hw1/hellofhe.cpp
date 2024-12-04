//#include "seal/seal.h"
//#include <iostream>
//
//using namespace std;
//using namespace seal;
//
//int main() {
//
//   cout << "Start" << endl;
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
//   cout << "Enc/Eval/Dec prepared!" << endl;
//
//   BatchEncoder encoder(context);              // ���� ���� �� ��ȣ���� �ֱ� ���� ���ڴ� ��ü ����
//   size_t slot_count = encoder.slot_count();   // �� ��ȣ���� � ������ ���� ���� �� �ִ°��� slot_count ������ ���� 
//   vector<uint64_t> plain_vector(slot_count, 0ULL);    // slot_count ������ ���Ҹ� ���ϴ� 0���� �̷���� ���� ����
//   plain_vector[0] = 3;        // ������ �Ϻ� ���ҿ� �� �Ҵ� : �̺κ��� ���� �����̳Ŀ� ���� �����Ͻø� �˴ϴ�.
//   plain_vector[1] = 5;
//   cout << "Input: " << plain_vector[0] << ", " << plain_vector[1] << ", " << plain_vector[2] << endl;
//
//
//   // ���� �����Ͽ� ���ڵ� (�� �� �޽��� ���͸� ��ȣȭ�ϱ� ���ؼ� ���¸� �����ϴ� ���̶� �����Ͻø� �˴ϴ�. ��Ȯ���� ���׽����� ����)
//   Plaintext plain;
//   encoder.encode(plain_vector, plain);
//
//   // ��ȣ�� ���� �� encrypted ��� ��ȣ���� �� ���� ��ȣȭ�� ����� ����
//   Ciphertext encrypted;
//   encryptor.encrypt(plain, encrypted);
//   cout << "Enc completed!" << endl;
//
//
//   // �� ��ȣ���� ������ �Ǵٸ� ��ȣ�� ���� 
//   Ciphertext encrypted2 = encrypted;
//   evaluator.add_inplace(encrypted, encrypted2); // �� ��ȣ���� ���� �� �� ����� encrypted�� ����
//   evaluator.multiply_inplace(encrypted, encrypted2); // encrypted�� encrypted2 ���Ѵ�.
//   cout << "Ciphertext computation completed!" << endl;
//
//   // ��ȣȭ ����� ������ ���� ����
//   Plaintext plain_result;
//   decryptor.decrypt(encrypted, plain_result);
//
//   // ��ȣȭ�� ���� �ٽ� �޽��� ���ͷ� ���ڵ�, ���� ��� ���
//   vector<uint64_t> result_vector;
//   encoder.decode(plain_result, result_vector);
//   cout << "End!" << endl;
//   cout << "Result: (input+input)*input: " << result_vector[0] << ", " << result_vector[1] << ", " << result_vector[2] << endl;
//
//   return 0;
//}
//
//
//
