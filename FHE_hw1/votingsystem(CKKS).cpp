#define MAX_CANDIDATE 4
#include "seal/seal.h"
#include <iostream>
#include <set> // ID 중복 확인용

using namespace seal;
using namespace std;

int main() {
    cout << "투표 시스템 시작." << endl;

    // 1. CKKS 파라미터 설정
    EncryptionParameters parms(scheme_type::ckks);
    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, { 60, 40, 40, 60 }));

    SEALContext context(parms);
    cout << "파라미터 설정 완료." << endl;

    // 2. 키 생성
    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    // CKKS 전용 인코더 생성
    CKKSEncoder encoder(context);
    size_t slot_count = encoder.slot_count();
    double scale = pow(2.0, 40); // CKKS는 스케일 설정 필요

    cout << "키 및 인코더 준비 완료. 슬롯 개수: " << slot_count << endl;

    // 3. 초기화
    Ciphertext total_votes;
    vector<double> initial_data(slot_count, 0.0); // 초기 데이터 (투표값만 포함)
    Plaintext plain_initial_data;

    encoder.encode(initial_data, scale, plain_initial_data);
    encryptor.encrypt(plain_initial_data, total_votes);

    cout << "투표 초기화 완료. " << endl;

    set<int> seen_ids; // 중복 투표 확인을 위한 ID 저장소

    while (true) {
        vector<double> vote_vector(slot_count, 0.0); // (투표값) 데이터
        int voter_id = 0, voted_candidate = 0;

        // 투표자 입력
        cout << "투표자 ID 입력 (0 입력 시 종료): ";
        cin >> voter_id;
        if (voter_id == 0) {
            cout << "투표를 종료합니다." << endl;
            break;
        }

        // 중복 확인
        if (seen_ids.find(voter_id) != seen_ids.end()) {
            cout << "중복 투표가 감지되었습니다. 이 투표는 무효화됩니다." << endl;
            continue;
        }
        seen_ids.insert(voter_id); // 새로운 ID 저장

        cout << "투표할 후보 선택 1.김재환 2.구자욱 3.최형우 4.손호영 : ";
        cin >> voted_candidate;
        if (voted_candidate <= 0 || voted_candidate > MAX_CANDIDATE) {
            cout << "올바르지 않은 후보입니다. 다시 시도하세요." << endl;
            continue;
        }

        // 투표값 설정
        vote_vector[voted_candidate - 1] += 1.0;

        // 평문 생성 및 암호화
        Plaintext plain_vote;
        encoder.encode(vote_vector, scale, plain_vote);

        Ciphertext encrypted_vote;
        encryptor.encrypt(plain_vote, encrypted_vote);

        cout << "암호화 완료." << endl;

        // 투표값 합산
        evaluator.add_inplace(total_votes, encrypted_vote);

        cout << "투표 합산 완료." << endl;
    }

    // 4. 복호화 및 최종 결과 출력
    Plaintext plain_result;
    decryptor.decrypt(total_votes, plain_result);

    vector<double> result_vector(slot_count);
    encoder.decode(plain_result, result_vector);

    cout << "복호화 완료. 투표 결과:" << endl;

    vector<double> candidate_votes(MAX_CANDIDATE, 0.0);
    for (int i = 0; i < MAX_CANDIDATE; ++i) {
        candidate_votes[i] = result_vector[i];
    }

    for (int i = 0; i < MAX_CANDIDATE; i++) {
        cout << "후보 " << (i + 1) << ": " << candidate_votes[i] << "표" << endl;
    }

    return 0;
}
