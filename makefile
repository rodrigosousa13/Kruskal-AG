main:
	gcc src/kruskal.c src/main.c include/cJSON.c -Iinclude -o main.exe

leetcode:
	gcc src/kruskal.c src/problem1579.c include/cJSON.c -Iinclude -o leetcode.exe
