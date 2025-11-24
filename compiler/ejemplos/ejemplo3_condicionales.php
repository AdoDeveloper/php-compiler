<?php
// Ejemplo 3: Bloques de decisión (if/else)

$edad = 18;
$mayor = $edad >= 18;

if ($mayor) {
    $mensaje = "Eres mayor de edad";
    echo $mensaje;
}

$nota = 85;
$aprobado = $nota >= 60;

if ($aprobado) {
    echo "Aprobado";
} else {
    echo "Reprobado";
}

// Comparaciones
$a = 10;
$b = 20;

if ($a < $b) {
    echo "a es menor que b";
}

if ($a != $b) {
    echo "a es diferente de b";
}

// Operadores lógicos
$x = 5;
$y = 10;
$z = 15;

$condicion1 = $x < $y;
$condicion2 = $y < $z;
$ambas = $condicion1 && $condicion2;

if ($ambas) {
    echo "Ambas condiciones son verdaderas";
}

// Operador OR
$esLunes = false;
$esViernes = true;
$finDeSemana = $esLunes || $esViernes;

if ($finDeSemana) {
    echo "Es inicio o fin de semana";
}

// Operador NOT
$llueve = false;
$noLlueve = !$llueve;

if ($noLlueve) {
    echo "No esta lloviendo";
}

?>
