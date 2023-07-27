class RegisterLoadTest {
    public static void main(String[] args) {
        int n1 = Integer.parseInt(args[0]);
        int n2 = Integer.parseInt(args[1]);
        int x1 = n1 + n2;
        int x2 = n1 - n2;
        int x3 = n1 * n2;
        int x4 = n2 - n1;
        int x5 = n1+2;
        int x6 = n2+2;
        int x7 = n1+3;
        int x8 = n2+3;
        int y1 = x1 * x2;
        int y2 = x3 * x4;
        int y3 = x5 * x6;
        int y4 = x7 * x8;
        int z1 = y1+y2;
        int z2 = y3-y4;
        int w = z1 + z2;

        System.out.println(w);
    }
}