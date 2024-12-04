#define MAX_CANDIDATE 4
#include "seal/seal.h"
#include <iostream>
#include <set> // ID �ߺ� Ȯ�ο�

using namespace seal;
using namespace std;

int main() {
    cout << "��ǥ �ý��� ����." << endl;

    // 1. CKKS �Ķ���� ����
    EncryptionParameters parms(scheme_type::ckks);
    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, { 60, 40, 40, 60 }));

    SEALContext context(parms);
    cout << "�Ķ���� ���� �Ϸ�." << endl;

    // 2. Ű ����
    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    // CKKS ���� ���ڴ� ����
    CKKSEncoder encoder(context);
    size_t slot_count = encoder.slot_count();
    double scale = pow(2.0, 40); // CKKS�� ������ ���� �ʿ�

    cout << "Ű �� ���ڴ� �غ� �Ϸ�. ���� ����: " << slot_count << endl;

    // 3. �ʱ�ȭ
    Ciphertext total_votes;
    vector<double> initial_data(slot_count, 0.0); // �ʱ� ������ (��ǥ���� ����)
    Plaintext plain_initial_data;

    encoder.encode(initial_data, scale, plain_initial_data);
    encryptor.encrypt(plain_initial_data, total_votes);

    cout << "��ǥ �ʱ�ȭ �Ϸ�. " << endl;

    set<int> seen_ids; // �ߺ� ��ǥ Ȯ���� ���� ID �����

    while (true) {
        vector<double> vote_vector(slot_count, 0.0); // (��ǥ��) ������
        int voter_id = 0, voted_candidate = 0;

        // ��ǥ�� �Է�
        cout << "��ǥ�� ID �Է� (0 �Է� �� ����): ";
        cin >> voter_id;
        if (voter_id == 0) {
            cout << "��ǥ�� �����մϴ�." << endl;
            break;
        }

        // �ߺ� Ȯ��
        if (seen_ids.find(voter_id) != seen_ids.end()) {
            cout << "�ߺ� ��ǥ�� �����Ǿ����ϴ�. �� ��ǥ�� ��ȿȭ�˴ϴ�." << endl;
            continue;
        }
        seen_ids.insert(voter_id); // ���ο� ID ����

        cout << "��ǥ�� �ĺ� ���� 1.����ȯ 2.���ڿ� 3.������ 4.��ȣ�� : ";
        cin >> voted_candidate;
        if (voted_candidate <= 0 || voted_candidate > MAX_CANDIDATE) {
            cout << "�ùٸ��� ���� �ĺ��Դϴ�. �ٽ� �õ��ϼ���." << endl;
            continue;
        }

        // ��ǥ�� ����
        vote_vector[voted_candidate - 1] += 1.0;

        // �� ���� �� ��ȣȭ
        Plaintext plain_vote;
        encoder.encode(vote_vector, scale, plain_vote);

        Ciphertext encrypted_vote;
        encryptor.encrypt(plain_vote, encrypted_vote);

        cout << "��ȣȭ �Ϸ�." << endl;

        // ��ǥ�� �ջ�
        evaluator.add_inplace(total_votes, encrypted_vote);

        cout << "��ǥ �ջ� �Ϸ�." << endl;
    }

    // 4. ��ȣȭ �� ���� ��� ���
    Plaintext plain_result;
    decryptor.decrypt(total_votes, plain_result);

    vector<double> result_vector(slot_count);
    encoder.decode(plain_result, result_vector);

    cout << "��ȣȭ �Ϸ�. ��ǥ ���:" << endl;

    vector<double> candidate_votes(MAX_CANDIDATE, 0.0);
    for (int i = 0; i < MAX_CANDIDATE; ++i) {
        candidate_votes[i] = result_vector[i];
    }

    for (int i = 0; i < MAX_CANDIDATE; i++) {
        cout << "�ĺ� " << (i + 1) << ": " << candidate_votes[i] << "ǥ" << endl;
    }

    return 0;
}
