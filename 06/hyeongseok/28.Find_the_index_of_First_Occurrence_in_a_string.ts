function strStr(haystack: string, needle: string): number {
    function getPartialMatch(needle: string): number[] {
        const pi = new Array(needle.length).fill(0);
        let start = 1, matched = 0;
        while (start + matched < needle.length) {
            if (needle[start + matched] === needle[matched]) {
                matched++;
                pi[start + matched - 1] = matched;
            } else {
                if (matched === 0) {
                    start++;
                } else {
                    start += matched - pi[matched - 1];
                    matched = pi[matched - 1];
                }
            }
        }
        return pi;
    }

    const pi = getPartialMatch(needle)

    let start = 0, match = 0;
    while (start <= haystack.length - needle.length) {
        if (haystack[start + match] == needle[match]) {
            match++
        }
        else {
            if (match == 0) start++
            else {
                start += match - pi[match - 1]
                match = pi[match - 1]
            }
        }
        if (match == needle.length) return start
    }

    return -1;
};

// function strStr(haystack: string, needle: string): number {
//     return haystack.indexOf(needle);
// };