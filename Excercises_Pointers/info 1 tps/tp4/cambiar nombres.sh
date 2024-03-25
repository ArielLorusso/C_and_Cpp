# para cambiar el caracteres del nombre de multples archivos con nombres similares
  for i in algo.2*; do echo "archivo: ${i} --> ${i/2/3}"; done 
# (cambia algo.2.1 algo.2.2 etc a algo.3.1 algo.3.2)
# para insertar caracteres al principio de multples archivos
  for i in *; do mv ${i} ejercicio${i}; done
# (agrega ejercicio al principio de cada archivo)