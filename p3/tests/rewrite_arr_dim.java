class Base {
    public static void main(String [] args) {
        System.out.println(args[0]);
        int [ ][ ] x = new int[2][2];
        x[0][0] = -1;
        x[0][1] = -1;
        x[1][0] = -1;
        x[1][1] = -1;
        int [ ] y = new int[2];
        y[0] = 5; y[1] = 3;
        x[0] = y;
        System.out.print(x[0][0]);
        System.out.println(x[0][1]);
        System.out.print(x[1][0]);
        System.out.println(x[1][1]);
        y[0] = 0; y[1] = 2;
        System.out.print(x[0][0]);
        System.out.println(x[0][1]);
    }
}