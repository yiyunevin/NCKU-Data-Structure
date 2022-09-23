# NCKU-Data-Structure

## Homework 1

由命令列讀取 testbench 檔案（數量不等），計算其中二維陣列 X、Y 之內積，並輸出至 out.txt 檔案。須將二維陣列轉換為一維陣列計算。

使用方式：
```bash
$ gcc -o main two_dim_mat_product.c
$ ./main testbench0.txt testbench1.txt
$ ./main testbench2.txt
```

## Homework 2

由命令列讀取 testbench 檔案（數量不等），化簡其中多項式並以降冪排列，將結果輸出至 out.txt 檔案。須使用 Circular Linked List (含 head 與 last) 完成。

使用方式：
```bash
$ gcc -o main circular_list_polinomial.c
$ ./main testbench1.txt testbench2.txt
$ ./main testbench2.txt
```

## Homework 3

由命令列讀取 testbench 檔案（數量不等），透過 Breadth First Search (BFS) 完成 maze routing 找出以最短路徑連接所有 Terminal 的方法，並將結果輸出至 out.txt 檔案。
+ 依照 x 由小到大、y 由小到大的方式排序各 Terminal 來決定連接先後順序
  + 先連接 T1 和 T2 得到 Path1，再由 T3 找到與 Path1 連接的最短路徑，以此類推
  + 若有 2 個以上的距離起始點相等且皆為最短距離的目標座標，則以 x 較小者優先
+ 回溯過程中，除非遇到障礙物，否則不須轉彎
+ testbench 中 Grid 為整體空間大小，Terminal 為指定端點，Disable region 則為不可通過的網格

使用方式：
```bash
$ gcc -o main bfs_maze_routing.c
$ ./main testbench1.txt testbench2.txt
$ ./main testbench2.txt
```
