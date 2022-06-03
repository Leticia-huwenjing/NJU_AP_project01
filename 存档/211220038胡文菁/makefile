INCLUDE = -I/home/huwenjing/project01/utf8

main:mk_wcwidth.o
	g++ main.cpp admin.cpp shopping.cpp buyer.cpp calculator.cpp seller.cpp sql.cpp user.cpp file.cpp mk_wcwidth.o utfwidth.cpp chatting.cpp -o main -std=c++17
mk_wcwidth.o:mk_wcwidth.c
	gcc -c mk_wcwidth.c -o mk_wcwidth.o
clean:
	rm *.o
	rm main