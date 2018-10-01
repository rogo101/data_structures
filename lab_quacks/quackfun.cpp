namespace QuackFun {

template <typename T>
T sum(stack<T>& s)
{
  if (s.size() > 0) {
    T a = s.top();
    s.pop();
    T b = sum(s);
    s.push(a);
    return a + b;
  }
  return T();
}

 bool isBalanced(queue<char> input)
 {
     stack<char> queueStack;
     while (input.empty() == false) {
       char a = input.front();
       input.pop();
       if (a == '[') {
         queueStack.push(a);
       }
       if (a == ']' && queueStack.empty()) {
         return false;
       }
       else if (a == ']'){
         queueStack.pop();
       }
     }
     if (queueStack.empty() == true) {
       return true;
     }
     else {
       return false;
     }
 }

template <typename T>
void scramble(queue<T>& q)
{
    queue<T> queue;
    stack<T> queueStack;
    int value = 1;
    queue.push(q.front());
    q.pop();

    while (q.empty() == false) {
      value++;
      if (value % 2 == 0) {
        for (int i = 0; i < value; i++) {
          if (q.empty() == false) {
            queueStack.push(q.front());
            q.pop();
          }
        }
        for (int j = 0; j < value; j++) {
          if (queueStack.empty() == false) {
            queue.push(queueStack.top());
            queueStack.pop();
          }
        }
      }
      else {
        for (int i = 0; i < value; i++) {
          if (q.empty() == false) {
            queue.push(q.front());
            q.pop();
          }
        }
      }
    }
    while (queue.empty() == false) {
      q.push(queue.front());
      queue.pop();
    }
}

template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool value = true;
    if(s.empty() == true) {
      return true;
    }
    T a = s.top();
    s.pop();
    if(a != q.front()) {
      value = false;
    }
    value = verifySame(s, q);
    T b = q.front();
    q.pop();
    value = (b == a && value);
    s.push(a);
    q.push(b);
    return value;
}

}
