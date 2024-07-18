function shortestPalindrome(s: string): string {
  function getPartialMatch(needle: string): number[] {
    const m = needle.length;
    const pi = new Array(m).fill(0);
    let j = 0;

    for (let i = 1; i < m; i++) {
      while (j > 0 && needle[i] !== needle[j]) {
        j = pi[j - 1];
      }
      if (needle[i] === needle[j]) {
        j++;
      }
      pi[i] = j;
    }
    return pi;
  }

  if (s.length === 0) return s;

  const rev = s.split("").reverse().join("");

  const combined = s + "#" + rev;
  const pi = getPartialMatch(combined);

  const maxMatch = pi[pi.length - 1];

  const prefixToAdd = rev.substring(0, rev.length - maxMatch);

  return prefixToAdd + s;
}
