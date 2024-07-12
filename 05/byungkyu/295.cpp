class MedianFinder {
public:

    priority_queue<int> pqs;
    priority_queue<int,vector<int>,greater<int> > pqb;

    MedianFinder() {
      
    }
    
    void addNum(int num) {
        if(pqs.size()>pqb.size()){
          pqb.push(num);
        }
        else pqs.push(num);
        if(pqs.size()&&pqb.size()){
          if(pqs.top()>pqb.top()){
            int s=pqs.top();pqs.pop();
            int b=pqb.top();pqb.pop();
            pqs.push(b);
            pqb.push(s);
          }
        }
    }
    
    double findMedian() {
        if(pqs.size()>pqb.size()){
          return (double)pqs.top();
        }
        return 1.0*((double)pqs.top()+(double)pqb.top())/2.0;
    }
};