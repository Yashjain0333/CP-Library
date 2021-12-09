struct minqueue {
    stack<pair<ll, ll>> front, back;
    void push(ll x) {
        if (front.empty()) {
            front.push({x, x});
            return;
        }
        front.push({x, min(x, front.top().second)});
    }
    void pop() {
        assert(front.size() + back.size());
        if (!back.empty()) {
            back.pop();
            return;
        }
        back.push({front.top().first, front.top().first});
        front.pop();
        while (!front.empty()) {
            back.push({front.top().first, min(front.top().first, back.top().second)});
            front.pop();
        }
        back.pop();
    }
    ll getmin() {
        assert(front.size() + back.size());
        if (front.empty()) {
            return back.top().second;
        }
        if (back.empty()) {
            return front.top().second;
        }
        return min(front.top().second, back.top().second);
    }
};