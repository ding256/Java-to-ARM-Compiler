// Type violation in line 8
// Binary operator '+' expects both left and right to be the same.
// left expression on line 8 was of type 'String[]'
// right expression on line 8 was of type 'int'

class Test {
    public static void main(String[] args) {
        System.out.println(args + 1);
    }
}
