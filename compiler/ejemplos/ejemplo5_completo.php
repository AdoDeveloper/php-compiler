<?php
// Ejemplo 5: Programa completo - Calculadora de promedio

// Inicialización de variables
$cantidad = 5;
$suma = 0;
$i = 0;

// Array simulado con variables individuales
$nota1 = 85;
$nota2 = 90;
$nota3 = 78;
$nota4 = 92;
$nota5 = 88;

// Sumar todas las notas
$suma = $nota1 + $nota2 + $nota3 + $nota4 + $nota5;
echo $suma;

// Calcular promedio
$promedio = $suma / $cantidad;
echo $promedio;

// Determinar si aprobó
$notaMinima = 60;
$aprobo = $promedio >= $notaMinima;

if ($aprobo) {
    echo "Aprobado con promedio";
    echo $promedio;

    // Verificar si es excelente
    $excelente = $promedio >= 90;
    if ($excelente) {
        echo "Calificacion excelente";
    }
} else {
    echo "Reprobado con promedio";
    echo $promedio;
}

// Contar cuántas notas son superiores al promedio
$superiores = 0;

if ($nota1 > $promedio) {
    $superiores++;
}
if ($nota2 > $promedio) {
    $superiores++;
}
if ($nota3 > $promedio) {
    $superiores++;
}
if ($nota4 > $promedio) {
    $superiores++;
}
if ($nota5 > $promedio) {
    $superiores++;
}

echo $superiores;

?>
