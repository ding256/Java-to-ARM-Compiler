class Base {
    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int [ ][ ] arr = new int[2][2];
        arr[0][0] = 1;
        arr[0][1] = 0;
        arr[1][0] = 3;
        arr[1][1] = 7;
        System.out.println(arr[1][0]);
    }
}