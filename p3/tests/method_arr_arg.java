class Base {
    public static int print_arr(int [ ] arr) {
        int i = 0, n = arr.length;
        while(i < n) {
            System.out.println(arr[i]);
            i = i + 1;
        }
        return 1;
    }

    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int [ ] arr = new int[3];
        arr[0] = 65;
        arr[1] = 76;
        arr[2] = 89;
        int a = print_arr(arr);
    }
}