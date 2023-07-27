class Base {
    public static int[] get_arr(int n) {
        int [ ] arr = new int[n];
        int i = 0;
        while(i < n) {
            arr[i] = i + 1;
            i = i + 1;
        }
        return arr;
    }

    public static void main(String [ ] args) {
        int m = 3;
        int [ ] arr = get_arr(m);
        int i = 0;
        while(i < m){
            System.out.print(arr[i]);
            i = i + 1;
        }
        System.out.println(args[0]);
    }
}