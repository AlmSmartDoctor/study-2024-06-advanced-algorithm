function strStr(haystack: string, needle: string): number {
  function getPartialMatch(needle: string): number[] {
    const m = needle.length;
    const pi = new Array(m).fill(0);
    let begin = 1;
    let matched = 0;
    while (begin + matched < m) {
      if (needle[begin + matched] === needle[matched]) {
        matched++;
        pi[begin + matched - 1] = matched;
      } else {
        if (matched === 0) {
          begin++;
        } else {
          begin += matched - pi[matched - 1];
          matched = pi[matched - 1];
        }
      }
    }
    return pi;
  }
  const n = haystack.length;
  const m = needle.length;
  const pi = getPartialMatch(needle);
  let begin = 0;
  let matched = 0;
  while (begin <= n - m) {
    if (matched < m && haystack[begin + matched] === needle[matched]) {
      matched++;
      if (matched === m) {
        return begin;
      }
    } else {
      if (matched === 0) {
        begin++;
      } else {
        begin += matched - pi[matched - 1];
        matched = pi[matched - 1];
      }
    }
  }
  return -1;
}
