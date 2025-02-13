#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll inf = 10000000000;

struct node {
    node *l, *r;
    ll key;
    node(){}
    node (ll key) : l(nullptr), r(nullptr), key (key){};
};

vector <ll> ordered;

node* root = nullptr;

bool exists (ll x){
    if (root == nullptr){
        return false;
    }
    node* cur = root;
    while (cur -> key != x){
        if (x < cur -> key){
            cur = cur -> l;
        } else {
            cur = cur -> r;
        }
        if (cur == nullptr){
            return false;
        }
    }
    return true;
}

void insert (ll x){
    if (root == nullptr){
        root = new node(x);
        return;
    }
    node* cur = root;
    while (true){
        if (x < cur -> key){
            if (cur -> l == nullptr){
                cur -> l = new node(x);
                return;
            }
            cur = cur -> l;
        } else {
            if (cur -> r == nullptr){
                cur -> r = new node(x);
                return;
            }
            cur = cur -> r;
        }
    }
}

void makeOrder (node* now){
    if (now != nullptr){
        makeOrder(now -> l);
        ordered.push_back(now -> key);
        makeOrder(now -> r);
    }
}

void remake (ll l, ll r){ //compile with 0, size of ordedred;
    if (r - l < 1){
        return;
    }
    ll m = (l + r) / 2;
    insert (ordered[m]);
    remake (l, m);
    remake (m + 1, r);
}

ll prev (ll x){
    node* cur = root;
    ll ans = inf;
    while (cur !=  nullptr){
      if (cur -> key >= x)
         cur = cur -> l;
      else {
         ans = cur -> key;
         cur = cur -> r;
      }
    }
    return ans;
} //if returns inf then must type "none"

ll next (ll x){
    node* cur = root;
    ll ans = inf;
    while (cur !=  nullptr){
      if (cur -> key > x) {
         ans = cur -> key;
         cur = cur -> l;
      }
      else
         cur = cur -> r;
    }
    return ans;
} //if returns inf then must type "none"

ll mini (node* cur){
    if (cur -> l == nullptr){
        return cur -> key;
    }
    return mini (cur -> l);
}

node* del (node* cur, node* parent, ll x){
    if (cur == nullptr){
        return cur;
    }
    if (x < cur -> key){
        cur -> l = del (cur -> l, cur, x);
    } else if (x > cur -> key){
        cur -> r = del (cur -> r, cur, x);
    } else if (cur -> l == nullptr && cur -> r == nullptr){
        if (parent == nullptr){
            cur = nullptr;
        }else if (parent -> l != nullptr && parent -> l -> key == x){
            parent -> l = nullptr;
        } else if (parent -> r != nullptr && parent -> r -> key == x){
            parent -> r = nullptr;
        }
        cur = nullptr;
    } else if (cur -> l != nullptr && cur -> r != nullptr){
        cur -> key = mini(cur -> r);
        cur -> r = del (cur -> r, cur, cur -> key);
    } else {
        if (cur -> l != nullptr){
            cur = cur -> l;
        } else {
            cur = cur -> r;
        }
    }
    return cur;
} //compile with root

int main()
{
    string s;
    ll counter;
    while (cin>>s){
        counter ++;
        ll x;
        cin>>x;
        if (counter % 10000 == 0){
            ordered.resize(0);
            makeOrder(root);
            /*for (int i = 0; i < ordered.size(); i++){
                cout<<ordered[i]<<' ';
            }
            cout<<endl;*/
            root = nullptr;
            remake(0, ordered.size());
        }
        if (s == "insert"){
            if (!exists(x)){
                insert (x);
            }
        } else if (s == "delete"){
            if (exists(x)){
                root = del (root, nullptr, x);
            }
        } else if (s == "exists"){
            bool ans = exists(x);
            if (ans){
                cout<<"true"<<"\n";
            } else
                cout<<"false"<<"\n";
        } else if (s == "prev"){
            ll ans = prev(x);
            if (ans == inf){
                cout<<"none"<<"\n";
            } else
                cout<<ans<<"\n";
        } else {
            ll ans = next(x);
            if (ans == inf){
                cout<<"none"<<"\n";
            } else
                cout<<ans<<"\n";
        }
    }
}
