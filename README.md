# Hyper_test

### 사용방법
## 컴파일 방법
1) 4개의 파일을 내려 받는다.(server.cpp, client.cpp, rmblank.cpp, calculator.cpp, test.txt)
2) Terminal1 [server] : g++ server.cpp -o server    
                        ./server
   Terminal2 [client] : g++ client.cpp -o client
                        ./client
3) 실행에 성공하면 client 에서 "Calculate with test.txt?[Y/N]"를 묻는다.
    -Y 선택 시 : "test.txt"에 있는 파일을 이용하여 자동으로 소켓통신이 이루어진다.
    -N 선택 시 : 표준입력으로 서버에 연산을 보내 결과를 받을 수 있다.

4) 결과는 Client terminal에서 소수점 5자리수까지 확인할 수 있다.

### 구현내용
1) 사칙연산, 음수, 괄호연산
2) 소수점 연산
