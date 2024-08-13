use std::cmp::min;

struct Solution {}

impl Solution {
    pub fn suggested_products(products: Vec<String>, search_word: String) -> Vec<Vec<String>> {
        let mut products = products;
        products.sort();
        let mut res = Vec::new();
        for i in 1..search_word.len() + 1 {
            let prefix = &search_word[0..i];
            let mut matchedWords = Vec::new();
            let mut count = 3;
            for product in products.iter() {
                if count > 0 {
                    if &product[0..min(i, product.len())] == prefix {
                        matchedWords.push(String::from(product));
                        count -= 1;
                    }
                } else {
                    break;
                }
            }
            res.push(matchedWords);
        }
        return res;
    }
}
