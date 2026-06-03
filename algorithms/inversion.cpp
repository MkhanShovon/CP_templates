ll merge_and_count(vector<ll>& arr, ll left, ll mid, ll right) {
    ll n1 = mid - left + 1;
    ll n2 = right - mid;

    // Create temp arrays
    vector<ll> left_arr(n1);
    vector<ll> right_arr(n2);

    // Copy data to temp arrays left_arr[] and right_arr[]
    for (ll i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];
    for (ll i = 0; i < n2; i++)
        right_arr[i] = arr[mid + 1 + i];

    ll i = 0; // Initial index of the first subarray
    ll j = 0; // Initial index of the second subarray
    ll k = left; // Initial index of the merged subarray
    ll inv_count = 0;

    // Merge the temp arrays back into arr[l..r]
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
            inv_count += (n1 - i); // Count inversions
        }
    }

    // Copy the remaining elements of left_arr[], if any
    while (i < n1)
        arr[k++] = left_arr[i++];

    // Copy the remaining elements of right_arr[], if any
    while (j < n2)
        arr[k++] = right_arr[j++];

    return inv_count;
}

// Function to use merge sort and count inversions
ll merge_sort_and_count(vector<ll>& arr, ll left, ll right) {
    ll inv_count = 0;
    if (left < right) {
        ll mid = left + (right - left) / 2;

        inv_count += merge_sort_and_count(arr, left, mid);
        inv_count += merge_sort_and_count(arr, mid + 1, right);
        inv_count += merge_and_count(arr, left, mid, right);
    }
    return inv_count;
}
