// [lo, hi)
// 000|111
// p(i) -> p(j), for all i < j, (e.g. i >= target)
template<class Predicate>
int lower_bound(int lo, int hi, Predicate p) {
    while (lo < hi) {
        int mid = lo+(hi-lo)/2;
        if (p(mid)) hi = mid;
        else        lo = mid+1;
    }
    if (!p(lo)) return hi;
    return lo;
}

// [lo, hi)
// 111|000
// p(i) <- p(j), for all i < j, (e.g. i <= target)
template<class Predicate>
int upper_bound(int lo, int hi, Predicate p) {
    while (lo < hi) {
        int mid = lo+(hi-lo)/2;
        if (p(mid)) lo = mid+1;
        else        hi = mid;
    }
    if (p(lo)) return hi;
    return lo;
}

cout << lower_bound(0, 10, [](auto x){ return x >= 3;}) << "\n";  // 3
cout << lower_bound(0, 10, [](auto x){ return x >= 11;}) << "\n"; // 10
cout << upper_bound(0, 10, [](auto x){ return x <= 3;}) << "\n";  // 4
cout << upper_bound(0, 10, [](auto x){ return x <= -1;}) << "\n"; // 0
