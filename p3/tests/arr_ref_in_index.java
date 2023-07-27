class Base {
    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int [ ] a = new int[3];
        a[0] = 2;
        a[1] = 5;
        a[2] = 9;
        int [ ] b = new int[3];
        b[0] = 2;
        b[1] = 0;
        System.out.println(a[b[0]]);
    }
}