class Base {
    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int [ ] a = new int[3];
        a[0] = 1;
        a[1] = 2;
        a[2] = 4;
        int [ ] b = new int[3];
        b[0] = 5;
        b[1] = 3;
        b[2] = 0;
        int ret = 0;
        int n = 2;
        while(n >= 0) {
            ret = ret + a[n] * b[n];
            n = n - 1;
        }
        System.out.println(ret);
    }
}