class ArrayGenerator {
private:
    static const int MAX_SIZE = 100000, MAX_VAL = 6001, MIN_SIZE = 500;
    vector<int> random_array, sorted_array, nearly_sorted_array;

    void generate_random() {
        for (int i = 0; i < MAX_SIZE; ++i) {
            random_array[i] = rnd() % MAX_VAL;
        }
    }

    void generate_sorted() {
        for (int i = 0; i < MAX_SIZE; ++i) {
            sorted_array[i] = rnd() % MAX_VAL;
        }
        sort(sorted_array.begin(), sorted_array.end());
        reverse(sorted_array.begin(), sorted_array.end());
    }

    void generate_nearly() {
        for (int i = 0; i < MAX_SIZE; ++i) {
            nearly_sorted_array[i] = rnd() % MAX_VAL;
        }
        sort(nearly_sorted_array.begin(), nearly_sorted_array.end());
        int n_swaps = rnd() % 30 + 5;
        while (n_swaps--) {
            int i = rnd() % MAX_SIZE;
            int j = i;
            while (j == i) {
                j = rnd() % MAX_SIZE;
            }
            swap(nearly_sorted_array[i], nearly_sorted_array[j]);
        }
    }
public:
    ArrayGenerator() {
        random_array.resize(MAX_SIZE);
        sorted_array.resize(MAX_SIZE);
        nearly_sorted_array.resize(MAX_SIZE);
        generate_random();
        generate_sorted();
        generate_nearly();
    }

    void get_random_array(int sz, vector<int>& ret) {
        int start = rnd() % (MAX_SIZE - sz);
        copy(random_array.begin() + start, random_array.begin() + start + sz, ret.begin());
    }

    void get_sorted_array(int sz, vector<int>& ret) {
        int start = rnd() % (MAX_SIZE - sz);
        copy(sorted_array.begin() + start, sorted_array.begin() + start + sz, ret.begin());
    }

    void get_nearly_sorted_array(int sz, vector<int>& ret) {
        int start = rnd() % (MAX_SIZE - sz);
        for(int i = 0; i < 5; i++)
            swap(nearly_sorted_array[rnd() % sz + start], nearly_sorted_array[rnd() % sz + start]);
        copy(nearly_sorted_array.begin() + start, nearly_sorted_array.begin() + start + sz, ret.begin());
    }

    void get_array(int sz, vector<int>& ret, char regime) {
        switch (regime) {
        case 'r':
            get_random_array(sz, ret);
            break;
        case 's':
            get_sorted_array(sz, ret);
            break;
        case 'n':
            get_nearly_sorted_array(sz, ret);
            break;
        }
    }
};
