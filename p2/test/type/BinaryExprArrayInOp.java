// Type violation in line 7
// Binary operator '+' expects both left and right to be the same.
// left expression on line 7 was of type 'int[]'
// right expression on line 7 was of type 'int'

class Test {
    private static int a = (new int[1]) + 2;
    public static void main(String[] args) {}
}
