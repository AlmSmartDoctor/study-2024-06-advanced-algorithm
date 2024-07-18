function shortestPalindrome(s: string): string {
    const partialMatch = (s: string): number[] => {
        const n = s.length
        const pi = Array(n)
        pi[0] = 0;

        for(let i = 1; i < n; i++) {
            let j = pi[i-1]
            while(j > 0 && s[j] != s[i]) {
                j = pi[j-1]
            }
            if (s[j] == s[i]) j++;
            pi[i] = j
        }

        return pi
    }

    // s: aacecaaa, sLen: 8
    const sLen = s.length;

    // aaacecaa
    const sRev = s.split('').reverse().join('');

    // aacecaaa#aaacecaa
    const sComb = `${s}#${sRev}`;

    // [a a c e c a a a # a a a c e c a a]
    // [0 1 0 0 0 1 2 2 0 1 2 2 3 4 5 6 7]
    const pi = partialMatch(sComb);

    // lps: 7
    const lps = pi.pop();
    
    // 'aaacecaa'.substring(0, 1) + aacecaaa
    return sRev.substring(0, sLen - lps) + s;
};