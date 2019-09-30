encode: encode.cpp
	g++ -o encode encode.cpp

decode: decode.cpp
	g++ -std=c++11 decode.cpp -o decode

