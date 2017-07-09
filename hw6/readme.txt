time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m56.997s
user	0m56.989s
sys	0m0.000s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m28.577s
user	0m56.844s
sys	0m0.000s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m14.361s
user	0m56.732s
sys	0m0.122s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m7.654s
user	0m57.569s
sys	0m0.081s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done


The benchmark shows that the "real" portion of calculation is approx. speeded up 
by the number of threads (actually lower), which meet the idea of parallelism. 

I observed the orginal implementation and fund that the for loop in in _tmain 
can be divided into different threads. So I wrote a function to store the part that
is safe to put in threads; then I allocated memory for threads and create/join the thread.

The biggest bug I met is I forget to rewrite MakeFile and the program cannot be compiled normally.