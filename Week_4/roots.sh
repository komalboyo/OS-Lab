# 3. Find all the possible quadratic equation roots using case.
#!/bin/bash
echo "Enter coefficients for the quadratic equation ax^2 + bx + c"
echo "Enter a:"
read a
echo "Enter b:"
read b
echo "Enter c:"
read c
# Calculate the discriminant
D=$((b * b - 4 * a * c))
# Use case to handle different values of the discriminant
case $D in
    # If D > 0
    [1-9]*)
        echo "Real and different roots"
        x1=$(( (-b - (D ** 0.5)) / (2 * a) ))
        x2=$(( (-b + (D ** 0.5)) / (2 * a) ))
        echo "x1 = $x1"
        echo "x2 = $x2"
        ;;
    # If D = 0
    0)
        echo "Real and same root"
        x=$(( -b / (2 * a) ))
        echo "x = $x"
        ;;
    # If D < 0
    *)
        echo "Imaginary roots"
        ;;
esac
