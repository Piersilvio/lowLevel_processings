# Low-Level Image Processing Toolkit

Questo progetto fornisce una semplice interfaccia in C++ e OpenCV per applicare **operazioni spaziali sulle immagini a basso livello**.  
È pensato per fini didattici e dimostrativi, offrendo una GUI testuale e alcune interazioni visive tramite slider (`cv::createTrackbar`).

---

## 🧠 Descrizione delle Funzionalità

### 1. 📊 Histogram
- Calcola e visualizza l'istogramma dei livelli di intensità.
- Implementato con `cv::calcHist` e disegno personalizzato in OpenCV.

### 2. ⚖️ Equalize Histogram
- Migliora il contrasto tramite `cv::equalizeHist()`.
- Utile per immagini con aree molto scure o molto chiare.

### 3. 🎯 Histogram Matching
- Confronta e adatta l’istogramma di un’immagine a quello di un’immagine target.
- Mappatura basata sulle distribuzioni cumulative.

### 4. ⬛ Invert Image
- Inversione per pixel: `255 - pixel`.
- Implementato manualmente (senza usare `bitwise_not`).

---

## 🔧 Filtri e Edge Detection

### 5. 🌫 Gaussian Blur
- Applica smoothing con filtro Gaussiano: `cv::GaussianBlur`.
- Controllo dinamico del **kernel size** con uno slider OpenCV.
- Solo valori dispari consentiti (3, 5, 7...).

### 6. 🟦 Sobel
- Calcolo del gradiente in X e Y: `cv::Sobel`.
- Somma pesata delle due direzioni per evidenziare i contorni.
- L'immagine viene convertita in scala di grigi se necessario.

### 7. 🟪 Roberts
- Operatore di bordo con kernel 2×2 (non disponibile direttamente in OpenCV).
- Implementato con `cv::filter2D` e kernel personalizzati:
  - `[[1, 0], [0, -1]]` per diagonale principale
  - `[[0, 1], [-1, 0]]` per diagonale inversa

---

## ✨ Sharpening con Laplaciano

### 8. 🔪 Sharpen Image (con Laplaciano)

- Il valore `c` è selezionabile dinamicamente:
  - `c = -1`: effetto nitido (sottrazione del Laplaciano)
  - `c = +1`: effetto più morbido (aggiunta del Laplaciano)
- Usato `cv::Laplacian` + `cv::addWeighted`.

---

## 🖱 Interazione Grafica

- I filtri dinamici (Gaussian, Sharpen) mostrano **sliders (trackbars)** per il controllo dei parametri in tempo reale.
- Ogni slider modifica l’immagine visualizzata all’istante.
- Finestra creata con `cv::namedWindow` + `cv::imshow` + `cv::createTrackbar`.

---

## 🛠 Requisiti

- OpenCV 4.x
- CMake
- Compilatore C++17 o superiore

