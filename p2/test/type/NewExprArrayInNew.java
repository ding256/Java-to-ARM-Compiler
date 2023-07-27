// Type violation in line 5
// new expression on line 5 on bracket expression 1 on line 5 is of type 'int[][]' but expected int type

class Test {
    private static int[] a = new int[new int[1][2]];
    public static void main(String[] args) {}
}
