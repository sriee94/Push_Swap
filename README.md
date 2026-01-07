# 🔄 Push_swap

> *An efficient sorting algorithm using two stacks and a limited set of operations*

**A sophisticated sorting implementation** featuring hardcoded optimizations for small datasets, chunk-based distribution, cost calculation, and simultaneous rotation optimization.

Built and maintained by **sriee94**.

---

## 🌐 Language / Langue

- [🇬🇧 English](#english)
- [🇫🇷 Français](#français)

---

<a name="english"></a>
# 🇬🇧 English

## 📖 Overview

Push_swap is a sorting algorithm project where you must sort a stack of integers using only **two stacks (a and b)** and a **limited set of operations**. The main challenge is finding an efficient algorithm that minimizes the number of operations for any given list of numbers.

### 🎯 Goals
- ✅ Sort any list of integers
- ✅ Use the minimum number of operations
- ✅ Meet strict performance requirements
- ✅ Handle edge cases and errors properly

### 📊 Performance Results

| Size | Operations | Target | Status |
|------|------------|--------|--------|
| **3 numbers** | 2-3 | ≤ 3 | ✅ |
| **5 numbers** | 8-12 | ≤ 12 | ✅ |
| **100 numbers** | ~610 | ≤ 700 | ✅ |
| **500 numbers** | ~5150 | ≤ 5500 | ✅ |

---

## 🚀 Installation and Usage

### Prerequisites
- C compiler (cc)
- Make
- Unix-based system (Linux, macOS)

### Clone the repository
```bash
git clone https://github.com/sriee94/push_swap.git
cd push_swap
```

### Compilation

```bash
# Compile push_swap
make

# Compile checker
make checker

# Clean object files
make clean

# Full cleanup
make fclean

# Recompile everything
make re
```

### Using push_swap

```bash
# Simple example
./push_swap 3 2 1 5 4

# Quoted arguments
./push_swap "3 2 1 5 4"

# Test with random numbers (100 numbers)
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' '); ./push_swap $ARG

# Count operations
./push_swap 3 2 1 5 4 | wc -l

# Verify sorting with checker
./push_swap 3 2 1 | ./checker 3 2 1
```

### Using checker

```bash
# Verify push_swap output
./push_swap 5 3 1 4 2 | ./checker 5 3 1 4 2
# Output: OK

# Manual test (end with Ctrl+D)
./checker 3 2 1
sa
pb
pa
^D
# Output: KO

# Test with echo
echo -e "sa\npb\npa" | ./checker 3 2 1
# Output: KO
```

---

## 🧠 Algorithm Explained

My implementation uses **3 different algorithms** based on stack size:

---

### 📌 Algorithm 1: For 2-3 Elements

#### For 2 elements
```c
if (size == 2 && a->content > a->next->content)
    sa(a);  // Single swap if needed
```

#### For 3 elements (`sort_three`)

All 6 possible configurations are **hardcoded** for maximum efficiency:

| Initial State | Operations | Result |
|---------------|------------|--------|
| `[1,2,3]` | ✅ Already sorted | `[1,2,3]` |
| `[2,1,3]` | `sa` | `[1,2,3]` |
| `[3,2,1]` | `sa` + `rra` | `[1,2,3]` |
| `[3,1,2]` | `ra` | `[1,2,3]` |
| `[2,3,1]` | `sa` + `ra` | `[1,2,3]` |
| `[1,3,2]` | `rra` | `[1,2,3]` |

**Example for `[3,2,1]`:**
```
[3, 2, 1]  →  sa   →  [2, 3, 1]
           →  rra  →  [1, 2, 3] ✅
```

---

### 📌 Algorithm 2: For 4-5 Elements (`sort_small`)

**Strategy:**
1. Push minimums to B until 3 elements remain in A
2. Sort the remaining 3 with `sort_three`
3. Push everything back from B to A

**Example with `[5, 3, 1, 4, 2]`:**

```bash
Initial: A:[5, 3, 1, 4, 2]  B:[]

# Push first minimum (1)
→ Find 1, rotate to top, pb
A:[4, 2, 5, 3]  B:[1]

# Push second minimum (2)
→ Find 2, rotate to top, pb
A:[5, 3, 4]  B:[2, 1]

# Sort remaining 3
→ sort_three([5, 3, 4])
A:[3, 4, 5]  B:[2, 1]

# Push back
→ pa, pa
A:[1, 2, 3, 4, 5] ✅  B:[]
```

**Optimization:** Uses `ra` or `rra` depending on minimum position (first half vs second half).

---

### 📌 Algorithm 3: For 100-500+ Elements (`sort_large`)

This is the main algorithm with 4 phases:

---

#### 🔸 Phase 1: Chunk-Based Distribution

**Concept:** Divide numbers into groups based on their sorted position, then push them to B in chunks.

```
Example: [7, 2, 9, 1, 5, 3, 8, 4, 6, 0]

Sorted reference: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
                  └─ chunk 1 ─┘ └─ chunk 2 ─┘ └ chunk 3
```

**Algorithm:**
```c
chunk_size = size / 5;  // For 100: 20 per chunk
                        // For 500: 100 per chunk
range = chunk_size;

while (*a) {
    current_index = get_index(sorted_array, size, (*a)->content);
    
    if (current_index < range) {
        pb(a, b);           // Push to B
        range += chunk_size; // Move to next chunk
    } else {
        ra(a);              // Keep searching
    }
}
```

**Result:** All numbers are in B, loosely grouped by size.

---

#### 🔸 Phase 2: Cost Calculation

For **each element in B**, calculate the total cost to move it to the correct position in A.

**Cost components:**

1. **`cost_b`**: Rotations to bring element to top of B
```c
if (position <= size / 2)
    cost_b = position;           // Use rb
else
    cost_b = -(size - position); // Use rrb
```

2. **`cost_a`**: Rotations to position element in A
```c
target_pos = find_target_position(value, stack_a);

if (target_pos <= size_a / 2)
    cost_a = target_pos;         // Use ra
else
    cost_a = -(size_a - target_pos); // Use rra
```

3. **Total cost with simultaneous rotation optimization:**
```c
if (cost_a > 0 && cost_b > 0)
    combined = max(cost_a, cost_b);      // Use rr
else if (cost_a < 0 && cost_b < 0)
    combined = max(abs(cost_a), abs(cost_b)); // Use rrr
else
    combined = abs(cost_a) + abs(cost_b);     // Different directions
```

**Example:**
```
Element at position 2, needs position 3 in A:
- cost_b = 2 (positive)
- cost_a = 3 (positive)

Without optimization: 2 rb + 3 ra = 5 operations
With optimization: 2 rr + 1 ra = 3 operations ✅
Savings: 40%!
```

Always choose the **element with minimum cost**.

---

#### 🔸 Phase 3: Optimized Execution

**Main loop:**
```c
while (*b) {
    1. find_cheapest_move()     // Find optimal element
    2. do_smart_rotations()     // Execute rr/rrr when possible
    3. finish_rotations()       // Complete remaining rotations
    4. pa(a, b)                 // Push to A
}
```

**Example:**
```
B: [8, 3, 1, 5]
A: [2, 4, 6]

Calculate costs:
- Element 8: cost = 5
- Element 3: cost = 2 ✅ (cheapest)
- Element 1: cost = 4
- Element 5: cost = 3

Execute for element 3:
→ rr (rotate both simultaneously)
→ pa
A: [3, 4, 6, 2]  B: [1, 5, 8]

Repeat until B is empty...
```

---

#### 🔸 Phase 4: Final Rotation

After pushing all elements back, the minimum isn't necessarily at the top.

```c
min_pos = find_min_position(stack_a);

if (min_pos <= size / 2)
    ra(a);   // Rotate up
else
    rra(a);  // Reverse rotate (shorter path)
```

**Example:**
```
[8, 1, 3, 2, 4, 6]  →  ra  →  [1, 3, 2, 4, 6, 8] ✅
     ↑ min at position 1
```

---

## 📊 Why It's Efficient

✅ **Chunks** → Prevents handling all numbers at once  
✅ **Cost calculation** → Always chooses optimal move  
✅ **Simultaneous rotations** → Saves 30-40% operations (rr/rrr)  
✅ **Smart positioning** → Uses shortest rotation path  
✅ **Hardcoded small cases** → Eliminates overhead for 2-5 elements

**Complexity:** O(n²) but heavily optimized with practical performance near O(n log n)

---

## 📁 Project Structure

```
push_swap/
├── Makefile
├── README.md
├── Include/
│   └── push_swap.h              # Main header
├── Libsriee/                    # Custom library
│   ├── Include/
│   ├── Src/
│   └── Makefile
├── Src/                         # push_swap source
│   ├── Main/
│   ├── Parsing/
│   ├── Operations/
│   │   ├── Push/
│   │   ├── Swap/
│   │   ├── Rotate/
│   │   └── Reverse/
│   ├── Algorithms/
│   │   ├── Basic/               # sort_three, sort_small
│   │   ├── Advanced/
│   │   ├── Chunks/
│   │   ├── Cost/
│   │   ├── Execute/
│   │   └── PushBack/
│   └── Utils/
└── Src-Checker/                 # Checker program
    ├── Main/
    ├── Execute-Operations/
    └── Operations-Silent/
```

---

## 🎮 Available Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap first 2 elements of A |
| `sb` | Swap first 2 elements of B |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push first element of B to A |
| `pb` | Push first element of A to B |
| `ra` | Rotate A up (first → last) |
| `rb` | Rotate B up |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate A (last → first) |
| `rrb` | Reverse rotate B |
| `rrr` | `rra` and `rrb` simultaneously |

---

## 🎁 Checker

The **checker** validates if a sequence of operations correctly sorts a stack.

### How it works
1. Takes the same arguments as push_swap
2. Reads operations from stdin (one per line)
3. Executes operations silently
4. Displays result:
   - ✅ `OK` if stack A is sorted and B is empty
   - ❌ `KO` if not sorted or B not empty
   - ⚠️ `Error` if invalid operation or arguments

### Examples

```bash
# Verify push_swap output
./push_swap 3 2 1 | ./checker 3 2 1
# Output: OK

# Manual test
echo -e "sa\npb\npa" | ./checker 3 2 1
# Output: KO

# Invalid operation
echo "invalid_op" | ./checker 3 2 1
# Output: Error
```

---

## ⚠️ Error Handling

The program displays **"Error"** on stderr for:
- ❌ Non-numeric arguments
- ❌ Duplicate numbers
- ❌ Integer overflow (> INT_MAX or < INT_MIN)
- ❌ Empty or invalid input
- ❌ Invalid operations (checker)

```bash
./push_swap 1 2 a        # Error
./push_swap 1 2 1        # Error
./push_swap 2147483648   # Error
./push_swap ""           # Error
```

---

## 🧪 Testing

### Basic tests
```bash
# Test 3 numbers
./push_swap 2 1 3 | wc -l    # Should be ≤ 3

# Test 5 numbers
./push_swap 5 3 1 4 2 | wc -l    # Should be ≤ 12

# Test 100 numbers
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
./push_swap $ARG | wc -l    # Should be ≤ 700

# Test 500 numbers
ARG=$(shuf -i 1-500 -n 500 | tr '\n' ' ')
./push_swap $ARG | wc -l    # Should be ≤ 5500
```

### Performance average
```bash
# Average for 100 numbers
for i in {1..10}; do
    ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
    ./push_swap $ARG | wc -l
done | awk '{sum+=$1} END {print "Average:", sum/NR}'
# Expected: ~610
```

### Memory check
```bash
valgrind --leak-check=full ./push_swap 3 2 1
# Expected: All heap blocks freed
```

---

## 👤 Author

**sriee94** - [GitHub](https://github.com/sriee94)

*Built with clean code principles and optimization in mind - 2025*

---

## 🔗 Related Projects

- [libsriee](https://github.com/sriee94/libsriee) - Custom C library
- [get_next_line](https://github.com/sriee94/get_next_line) - Line reading function
- [ft_printf](https://github.com/sriee94/ft_printf) - Custom printf implementation

---

**⭐ If you find this useful, consider giving it a star!**

---
---

<a name="français"></a>
# 🇫🇷 Français

## 📖 Aperçu

Push_swap est un projet d'algorithme de tri où vous devez trier une pile d'entiers en utilisant seulement **deux piles (a et b)** et un **ensemble limité d'opérations**. Le défi principal est de trouver un algorithme efficace qui minimise le nombre de mouvements pour n'importe quelle liste de nombres.

### 🎯 Objectifs
- ✅ Trier n'importe quelle liste d'entiers
- ✅ Utiliser le minimum d'opérations
- ✅ Respecter des exigences de performance strictes
- ✅ Gérer les cas limites et les erreurs correctement

### 📊 Résultats de Performance

| Taille | Opérations | Cible | Statut |
|--------|------------|-------|--------|
| **3 nombres** | 2-3 | ≤ 3 | ✅ |
| **5 nombres** | 8-12 | ≤ 12 | ✅ |
| **100 nombres** | ~610 | ≤ 700 | ✅ |
| **500 nombres** | ~5150 | ≤ 5500 | ✅ |

---

## 🚀 Installation et Utilisation

### Prérequis
- Compilateur C (cc)
- Make
- Système Unix (Linux, macOS)

### Cloner le dépôt
```bash
git clone https://github.com/sriee94/push_swap.git
cd push_swap
```

### Compilation

```bash
# Compiler push_swap
make

# Compiler le checker
make checker

# Nettoyer les fichiers objets
make clean

# Nettoyage complet
make fclean

# Recompiler tout
make re
```

### Utiliser push_swap

```bash
# Exemple simple
./push_swap 3 2 1 5 4

# Arguments entre guillemets
./push_swap "3 2 1 5 4"

# Tester avec des nombres aléatoires (100 nombres)
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' '); ./push_swap $ARG

# Compter les opérations
./push_swap 3 2 1 5 4 | wc -l

# Vérifier le tri avec le checker
./push_swap 3 2 1 | ./checker 3 2 1
```

### Utiliser le checker

```bash
# Vérifier la sortie de push_swap
./push_swap 5 3 1 4 2 | ./checker 5 3 1 4 2
# Sortie: OK

# Test manuel (terminer avec Ctrl+D)
./checker 3 2 1
sa
pb
pa
^D
# Sortie: KO

# Test avec echo
echo -e "sa\npb\npa" | ./checker 3 2 1
# Sortie: KO
```

---

## 🧠 Explication de l'Algorithme

Mon implémentation utilise **3 algorithmes différents** selon la taille de la pile :

---

### 📌 Algorithme 1 : Pour 2-3 Éléments

#### Pour 2 éléments
```c
if (size == 2 && a->content > a->next->content)
    sa(a);  // Un seul swap si nécessaire
```

#### Pour 3 éléments (`sort_three`)

Toutes les 6 configurations possibles sont **hardcodées** pour une efficacité maximale :

| État Initial | Opérations | Résultat |
|--------------|------------|----------|
| `[1,2,3]` | ✅ Déjà trié | `[1,2,3]` |
| `[2,1,3]` | `sa` | `[1,2,3]` |
| `[3,2,1]` | `sa` + `rra` | `[1,2,3]` |
| `[3,1,2]` | `ra` | `[1,2,3]` |
| `[2,3,1]` | `sa` + `ra` | `[1,2,3]` |
| `[1,3,2]` | `rra` | `[1,2,3]` |

**Exemple pour `[3,2,1]` :**
```
[3, 2, 1]  →  sa   →  [2, 3, 1]
           →  rra  →  [1, 2, 3] ✅
```

---

### 📌 Algorithme 2 : Pour 4-5 Éléments (`sort_small`)

**Stratégie :**
1. Push les minimums vers B jusqu'à avoir 3 éléments dans A
2. Trier les 3 restants avec `sort_three`
3. Tout ramener depuis B vers A

**Exemple avec `[5, 3, 1, 4, 2]` :**

```bash
Initial: A:[5, 3, 1, 4, 2]  B:[]

# Push premier minimum (1)
→ Trouve 1, rotate en haut, pb
A:[4, 2, 5, 3]  B:[1]

# Push deuxième minimum (2)
→ Trouve 2, rotate en haut, pb
A:[5, 3, 4]  B:[2, 1]

# Trier les 3 restants
→ sort_three([5, 3, 4])
A:[3, 4, 5]  B:[2, 1]

# Ramener depuis B
→ pa, pa
A:[1, 2, 3, 4, 5] ✅  B:[]
```

**Optimisation :** Utilise `ra` ou `rra` selon la position du minimum (première moitié vs seconde moitié).

---

### 📌 Algorithme 3 : Pour 100-500+ Éléments (`sort_large`)

C'est l'algorithme principal avec 4 phases :

---

#### 🔸 Phase 1 : Distribution par Chunks

**Concept :** Diviser les nombres en groupes selon leur position dans l'ordre trié, puis les push vers B par chunks.

```
Exemple : [7, 2, 9, 1, 5, 3, 8, 4, 6, 0]

Référence triée : [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
                  └─ chunk 1 ─┘ └─ chunk 2 ─┘ └ chunk 3
```

**Algorithme :**
```c
chunk_size = size / 5;  // Pour 100: 20 par chunk
                        // Pour 500: 100 par chunk
range = chunk_size;

while (*a) {
    current_index = get_index(sorted_array, size, (*a)->content);
    
    if (current_index < range) {
        pb(a, b);           // Push vers B
        range += chunk_size; // Passer au chunk suivant
    } else {
        ra(a);              // Continuer la recherche
    }
}
```

**Résultat :** Tous les nombres sont dans B, vaguement groupés par taille.

---

#### 🔸 Phase 2 : Calcul de Coût

Pour **chaque élément dans B**, calculer le coût total pour le ramener à la bonne position dans A.

**Composantes du coût :**

1. **`cost_b`** : Rotations pour amener l'élément en haut de B
```c
if (position <= size / 2)
    cost_b = position;           // Utilise rb
else
    cost_b = -(size - position); // Utilise rrb
```

2. **`cost_a`** : Rotations pour positionner l'élément dans A
```c
target_pos = find_target_position(value, stack_a);

if (target_pos <= size_a / 2)
    cost_a = target_pos;         // Utilise ra
else
    cost_a = -(size_a - target_pos); // Utilise rra
```

3. **Coût total avec optimisation des rotations simultanées :**
```c
if (cost_a > 0 && cost_b > 0)
    combined = max(cost_a, cost_b);      // Utilise rr
else if (cost_a < 0 && cost_b < 0)
    combined = max(abs(cost_a), abs(cost_b)); // Utilise rrr
else
    combined = abs(cost_a) + abs(cost_b);     // Directions différentes
```

**Exemple :**
```
Élément à position 2, besoin position 3 dans A :
- cost_b = 2 (positif)
- cost_a = 3 (positif)

Sans optimisation : 2 rb + 3 ra = 5 opérations
Avec optimisation : 2 rr + 1 ra = 3 opérations ✅
Économie : 40% !
```

Toujours choisir **l'élément avec le coût minimum**.

---

#### 🔸 Phase 3 : Exécution Optimisée

**Boucle principale :**
```c
while (*b) {
    1. find_cheapest_move()     // Trouver l'élément optimal
    2. do_smart_rotations()     // Exécuter rr/rrr quand possible
    3. finish_rotations()       // Terminer les rotations restantes
    4. pa(a, b)                 // Push vers A
}
```

**Exemple :**
```
B: [8, 3, 1, 5]
A: [2, 4, 6]

Calculer les coûts :
- Élément 8 : coût = 5
- Élément 3 : coût = 2 ✅ (le moins cher)
- Élément 1 : coût = 4
- Élément 5 : coût = 3

Exécuter pour l'élément 3 :
→ rr (rotate les deux simultanément)
→ pa
A: [3, 4, 6, 2]  B: [1, 5, 8]

Répéter jusqu'à ce que B soit vide...
```

---

#### 🔸 Phase 4 : Rotation Finale

Après avoir ramené tous les éléments, le minimum n'est pas forcément en haut.

```c
min_pos = find_min_position(stack_a);

if (min_pos <= size / 2)
    ra(a);   // Rotate vers le haut
else
    rra(a);  // Reverse rotate (chemin plus court)
```

**Exemple :**
```
[8, 1, 3, 2, 4, 6]  →  ra  →  [1, 3, 2, 4, 6, 8] ✅
     ↑ min à la position 1
```

---

## 📊 Pourquoi C'est Efficace

✅ **Chunks** → Évite de gérer tous les nombres d'un coup  
✅ **Calcul de coût** → Choisit toujours le mouvement optimal  
✅ **Rotations simultanées** → Économise 30-40% d'opérations (rr/rrr)  
✅ **Positionnement intelligent** → Utilise le chemin de rotation le plus court  
✅ **Cas petits hardcodés** → Élimine les calculs superflus pour 2-5 éléments

**Complexité :** O(n²) mais fortement optimisé avec performance pratique proche de O(n log n)

---

## 📁 Structure du Projet

```
push_swap/
├── Makefile
├── README.md
├── Include/
│   └── push_swap.h              # Header principal
├── Libsriee/                    # Bibliothèque personnalisée
│   ├── Include/
│   ├── Src/
│   └── Makefile
├── Src/                         # Code push_swap
│   ├── Main/
│   ├── Parsing/
│   ├── Operations/
│   │   ├── Push/
│   │   ├── Swap/
│   │   ├── Rotate/
│   │   └── Reverse/
│   ├── Algorithms/
│   │   ├── Basic/               # sort_three, sort_small
│   │   ├── Advanced/
│   │   ├── Chunks/
│   │   ├── Cost/
│   │   ├── Execute/
│   │   └── PushBack/
│   └── Utils/
└── Src-Checker/                 # Programme checker
    ├── Main/
    ├── Execute-Operations/
    └── Operations-Silent/
```

---

## 🎮 Opérations Disponibles

| Opération | Description |
|-----------|-------------|
| `sa` | Swap les 2 premiers éléments de A |
| `sb` | Swap les 2 premiers éléments de B |
| `ss` | `sa` et `sb` simultanément |
| `pa` | Push le premier élément de B vers A |
| `pb` | Push le premier élément de A vers B |
| `ra` | Rotate A vers le haut (premier → dernier) |
| `rb` | Rotate B vers le haut |
| `rr` | `ra` et `rb` simultanément |
| `rra` | Reverse rotate A (dernier → premier) |
| `rrb` | Reverse rotate B |
| `rrr` | `rra` et `rrb` simultanément |

---

## 🎁 Checker

Le **checker** valide si une séquence d'opérations trie correctement une pile.

### Comment ça fonctionne
1. Prend les mêmes arguments que push_swap
2. Lit les opérations depuis stdin (une par ligne)
3. Exécute les opérations silencieusement
4. Affiche le résultat :
   - ✅ `OK` si la pile A est triée et B est vide
   - ❌ `KO` si pas triée ou B pas vide
   - ⚠️ `Error` si opération ou arguments invalides

### Exemples

```bash
# Vérifier la sortie de push_swap
./push_swap 3 2 1 | ./checker 3 2 1
# Sortie: OK

# Test manuel
echo -e "sa\npb\npa" | ./checker 3 2 1
# Sortie: KO

# Opération invalide
echo "invalid_op" | ./checker 3 2 1
# Sortie: Error
```

---

## ⚠️ Gestion d'Erreurs

Le programme affiche **"Error"** sur stderr pour :
- ❌ Arguments non numériques
- ❌ Nombres dupliqués
- ❌ Dépassement d'entier (> INT_MAX ou < INT_MIN)
- ❌ Entrée vide ou invalide
- ❌ Opérations invalides (checker)

```bash
./push_swap 1 2 a        # Error
./push_swap 1 2 1        # Error
./push_swap 2147483648   # Error
./push_swap ""           # Error
```

---

## 🧪 Tests

### Tests de base
```bash
# Test 3 nombres
./push_swap 2 1 3 | wc -l    # Devrait être ≤ 3

# Test 5 nombres
./push_swap 5 3 1 4 2 | wc -l    # Devrait être ≤ 12

# Test 100 nombres
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
./push_swap $ARG | wc -l    # Devrait être ≤ 700

# Test 500 nombres
ARG=$(shuf -i 1-500 -n 500 | tr '\n' ' ')
./push_swap $ARG | wc -l    # Devrait être ≤ 5500
```

### Moyenne de performance
```bash
# Moyenne pour 100 nombres
for i in {1..10}; do
    ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
    ./push_swap $ARG | wc -l
done | awk '{sum+=$1} END {print "Moyenne:", sum/NR}'
# Attendu: ~610
```

### Vérification mémoire
```bash
valgrind --leak-check=full ./push_swap 3 2 1
# Attendu: Tous les blocs libérés
```

---

## 👤 Auteur

**sriee94** - [GitHub](https://github.com/sriee94)

*Construit avec des principes de code propre et d'optimisation à l'esprit - 2025*

---

## 🔗 Projets Liés

- [libsriee](https://github.com/sriee94/libsriee) - Bibliothèque C personnalisée
- [get_next_line](https://github.com/sriee94/get_next_line) - Fonction de lecture de ligne
- [ft_printf](https://github.com/sriee94/ft_printf) - Implémentation personnalisée de printf

---

**⭐ Si vous trouvez cela utile, pensez à mettre une étoile !**