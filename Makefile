compress1:
	cc -c index.c -Wall
	cc -c frequency.c -Wall
	cc -c huffman_tree.c -Wall
	cc -c list.c -Wall
	cc index.o frequency.o huffman_tree.o list.o -o run -lm
	./run -c1 SampleTextFile_500kb.txt testcompressed_huffman
	rm run index.o frequency.o huffman_tree.o list.o
decompress1:
	cc -c index.c -Wall
	cc -c frequency.c -Wall
	cc -c huffman_tree.c -Wall
	cc -c list.c -Wall
	cc index.o frequency.o huffman_tree.o list.o -o run -lm
	./run -uc1 testcompressed_huffman test1.txt
	rm run index.o frequency.o huffman_tree.o list.o
compress2:
	cc -c index.c -Wall
	cc -c frequency.c -Wall
	cc -c huffman_tree.c -Wall
	cc -c list.c -Wall
	cc index.o frequency.o huffman_tree.o list.o -o run -lm
	./run -c2 SampleTextFile_500kb.txt testcompressed
	rm run index.o frequency.o huffman_tree.o list.o
decompress2:
	cc -c index.c -Wall
	cc -c frequency.c -Wall
	cc -c huffman_tree.c -Wall
	cc -c list.c -Wall
	cc index.o frequency.o huffman_tree.o list.o -o run -lm
	./run -uc2 testcompressed test1.txt
	rm run index.o frequency.o huffman_tree.o list.o
