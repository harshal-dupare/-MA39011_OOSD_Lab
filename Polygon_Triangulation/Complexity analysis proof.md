

### Complexity analysis proof


$$
k_1+k_2+...+k_m = 2n\\
T = k_1log(k_1)+k_2log(k_2)+...+k_mlog(k_m)\\
T = log(\Pi k_i^{k_i})\\
e^T = \Pi k_i^{k_i}\\
by\ weighted\ AM-GM \\
(\Pi k_i^{k_i})^{\frac{1}{\sum\limits_{i=1}^{m} k_i}} = (\Pi k_i^{k_i})^{\frac{1}{(2n)}} \le \frac{\sum\limits_{i=1}^{m} k_i*k_i}{\sum\limits_{i=1}^{m} k_i}\\
\frac{\sum\limits_{i=1}^{m} k_i*k_i}{\sum\limits_{i=1}^{m} k_i} \le \frac{(\sum\limits_{i=1}^{m} k_i)^2 }{\sum\limits_{i=1}^{m} k_i} \le \sum\limits_{i=1}^{m} k_i =2n\\
(\Pi k_i^{k_i})^{\frac{1}{2n}} \le 2n \\
e^T \le (2n)^{2n}\\
T \le 2n\cdot log(2n)\\
T = O(n\cdot log(n))
$$
