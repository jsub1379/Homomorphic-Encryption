#이해한 내용
투표 받아서 plain_vector에 저장
plain 평문 생성, 인코딩
encrypted 암호문 생성, 공개 키로 암호화 후 저장
total_votes는 암호문인 상태로 저장 ex)서버
모두 저장 후,  관리자가 개인 키로 복호화 후 plain_result에 저장
result_vector에 디코딩 후 저장
결과는 result_vector에 출력
서버는 암호화된 정보를 합산해서 전달할 뿐, 안의 내용 확인 불가
