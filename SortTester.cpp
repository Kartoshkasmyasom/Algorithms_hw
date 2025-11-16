int K = 15; // threshold
class SortTester {
    ArrayGenerator* generator;
    static const int MAX_SIZE = 100000, TRIES = 5;;
public:

    SortTester() {
        generator = new ArrayGenerator();
    }

    pair<ll, ll> check_time_twice(int sz, char regime, vector<int>& v1, vector<int>& v2) {
                generator->get_array(sz, v1, regime);
                copy(v1.begin(), v1.end(), v2.begin());

                auto start1 = std::chrono::high_resolution_clock::now();
                merge_sort(v1, 0, sz);
                auto elapsed1 = std::chrono::high_resolution_clock::now() - start1;
                ll msec1 = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed1).count();

                auto start2 = std::chrono::high_resolution_clock::now();
                merge_sort_hybrid(v2, 0, sz);
                auto elapsed2 = std::chrono::high_resolution_clock::now() - start2;
                ll msec2 = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed2).count();
            return { msec1, msec2 };
    }

    ll check_time(int sz, char regime, vector<int>& v) {
        generator->get_array(sz, v, regime);
        auto start1 = std::chrono::high_resolution_clock::now();
        merge_sort_hybrid(v, 0, sz);
        auto elapsed1 = std::chrono::high_resolution_clock::now() - start1;
        ll msec1 = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed1).count();
        return msec1;
    }

    void test_diff_with_merge_sort() {
        vector<int> v1(MAX_SIZE), v2(MAX_SIZE);
        vector<int> sizes = { 500, 1000, 5000 };
        for (int i = 10000; i < MAX_SIZE; i += 10000)
            sizes.push_back(i);
        vector<ll> ms_rand(sizes.size()), msh_rand(sizes.size());
        vector<ll> ms_s(sizes.size()), msh_s(sizes.size());
        vector<ll> ms_n(sizes.size()), msh_n(sizes.size());
        for (int i = 0; i < sizes.size(); i++) {
            for (int j = 0; j < TRIES; j++) {
                auto time_r = check_time_twice(sizes[i], 'r', v1, v2);
                auto time_s = check_time_twice(sizes[i], 's', v1, v2);
                auto time_n = check_time_twice(sizes[i], 'n', v1, v2);
                ms_rand[i] += time_r.first;
                msh_rand[i] += time_r.second;
                ms_s[i] += time_s.first;
                msh_s[i] += time_s.second;
                ms_n[i] += time_n.first;
                msh_n[i] += time_n.second;
            }
            ms_rand[i] /= TRIES; msh_rand[i] /= TRIES;
            ms_s[i] /= TRIES; msh_s[i] /= TRIES;
            ms_n[i] /= TRIES; msh_n[i] /= TRIES;
        }
     
        cout << "merge sort on random:\n";
        for (int i = 0; i < sizes.size(); i++) {
            cout << sizes[i] << ' ' << ms_rand[i] << '\n';
        }

        cout << "hybrid merge sort on random:\n";
        for (int i = 0; i < sizes.size(); i++) {
            cout << sizes[i] << ' ' << msh_rand[i] << '\n';
        }

        cout << "merge sort on sorted:\n";
        for (int i = 0; i < sizes.size(); i++) {
            cout << sizes[i] << ' ' << ms_s[i] << '\n';
        }

        cout << "hybrid merge sort on sorted:\n";
        for (int i = 0; i < sizes.size(); i++) {
            cout << sizes[i] << ' ' << msh_s[i] << '\n';
        }

        cout << "merge sort on nearly sorted:\n";
        for (int i = 0; i < sizes.size(); i++) {
            cout << sizes[i] << ' ' << ms_n[i] << '\n';
        }

        cout << "hybrid merge sort on nearly sorted:\n";
        for (int i = 0; i < sizes.size(); i++) {
            cout << sizes[i] << ' ' << msh_n[i] << '\n';
        }
    }

    void test_diff_thresholds() {
        vector<int> t = { 5, 10, 20, 30, 50 };
        vector<int> v1(MAX_SIZE);
        vector<int> sizes = { 500, 1000, 5000 };
        for (int i = 10000; i < MAX_SIZE; i += 10000)
            sizes.push_back(i);
        vector<vector<ll>> msh(sizes.size(), vector<ll>(3));
        vector<char> regimes = { 'r', 's', 'n' };
        for (auto th : t) {
            K = th;
            for (int i = 0; i < sizes.size(); i++) {
                for (int j = 0; j < TRIES; j++) {
                    for (int k = 0; k < 3; k++) {
                        msh[i][k] += check_time(sizes[i], regimes[k], v1);
                    }
                }
                for (int k = 0; k < 3; k++) {
                    msh[i][k] /= TRIES;
                }
            }
            cout << "hybrid merge sort on random with threshold: " << th << "\n";
            for (int i = 0; i < sizes.size(); i++) {
                cout << sizes[i] << ' ' << msh[i][0] << "\n";
            }

            cout << "hybrid merge sort on sorted with threshold: " << th << "\n";
            for (int i = 0; i < sizes.size(); i++) {
                cout << sizes[i] << ' ' << msh[i][1] << "\n";
            }

            cout << "hybrid merge nearly sorted with threshold: " << th << "\n";
            for (int i = 0; i < sizes.size(); i++) {
                cout << sizes[i] << ' ' << msh[i][2] << "\n";
            }
        }

    }
};
