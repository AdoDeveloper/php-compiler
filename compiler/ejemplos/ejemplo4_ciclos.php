<?php
// Ejemplo 4: Bloques de repetición

// Ciclo WHILE
$contador = 0;
while ($contador < 5) {
    echo $contador;
    $contador++;
}

// Ciclo FOR
$i = 0;
for ($i = 0; $i < 10; $i++) {
    echo $i;
}

// Ciclo DO-WHILE
$n = 1;
do {
    echo $n;
    $n++;
} while ($n <= 5);

// Suma de números del 1 al 10
$suma = 0;
$num = 1;
while ($num <= 10) {
    $suma += $num;
    $num++;
}
echo $suma;

// Factorial de un número
$factorial = 1;
$numero = 5;
$j = 1;
while ($j <= $numero) {
    $factorial *= $j;
    $j++;
}
echo $factorial;

?>
