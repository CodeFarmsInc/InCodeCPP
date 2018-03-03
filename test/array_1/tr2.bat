call clean
..\..\codegen -dol -flex ds.def ..\..\lib gen -genLib tmp1
cl array_1.cpp 
array_1 array_1.inp array_1.res
..\diff array_1.res array_1.out
