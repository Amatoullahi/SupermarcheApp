const API = 'http://127.0.0.1:8080/api';
// Initialisation du graphique (une seule fois au chargement)
const ctx = document.getElementById('monGraphique').getContext('2d');
const monChart = new Chart(ctx, {
    type: 'bar',
    data: {
        labels: [],
        datasets: [{
            label: 'Clients en attente',
            data: [],
            backgroundColor: [],
        }]
    },
    options: {
        responsive: true,
        scales: { y: { beginAtZero: true, ticks: { stepSize: 1 } } }
    }
});

// Fonction de mise à jour du graphique
function mettreAJourGraphique(caisses) {
    monChart.data.labels = caisses.map(c =>
        'Caisse ' + c.numero + (c.express ? ' ⚡' : '')
    );
    monChart.data.datasets[0].data = caisses.map(c => c.nbClients);
    monChart.data.datasets[0].backgroundColor = caisses.map(c =>
        c.nbClients > 5 ? '#e74c3c' :
        c.express       ? '#f5a623' : '#1A3A6B'
    );
    monChart.update();
}
// Affiche un message temporaire en bas à droite
function afficherMessage(texte, type) {
  const msg = document.getElementById('message');
  msg.textContent = texte;
  msg.className = type;
  msg.style.display = 'block';
  setTimeout(() => msg.style.display = 'none', 3000);
}

// Interroge le serveur et met à jour l'affichage
async function rafraichir() {
  try {
    const res  = await fetch(`${API}/etat`);
    const data = await res.json();
    afficherCaisses(data.caisses);
    document.getElementById('totalServis').textContent = data.totalServis;
    mettreAJourGraphique(data.caisses);
  } catch (e) {
    console.error('Serveur inaccessible', e);
  }
}

// Génère les cartes HTML
function afficherCaisses(caisses) {
  const grille = document.getElementById('grille-caisses');
  grille.innerHTML = '';
  caisses.forEach(c => {
    const carte = document.createElement('div');
    carte.className = 'carte-caisse' +
      (c.express   ? ' express' : '') +
      (!c.ouverte  ? ' fermee'  : '') +
      (c.nbClients > 5 ? ' alerte' : '');

    carte.innerHTML = `
      <h3>Caisse ${c.numero}
        ${c.express ? '<span class="badge-express">EXPRESS</span>' : ''}
      </h3>
      <p>👥 Clients en attente : <strong>${c.nbClients}</strong></p>
      <p>⏱️ Temps d'attente : ~${c.tempsAttente}s</p>
      <p>${c.ouverte ? '🟢 Ouverte' : '🔴 Fermée'}</p>
    `;
    grille.appendChild(carte);
  });
}

// Ajouter un client
async function ajouterClient() {
  const nom = document.getElementById('nomClient').value.trim();
  const nb  = parseInt(document.getElementById('nbArticles').value);
  if (!nom || isNaN(nb) || nb < 1) {
    afficherMessage('Remplis le nom et le nombre d\'articles !', 'erreur');
    return;
  }
  try {
    const res = await fetch(`${API}/client/ajouter`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ nom, nbArticles: nb })
    });
    const data = await res.json();
    if (data.erreur) { afficherMessage(data.erreur, 'erreur'); return; }
    afficherMessage(`${nom} ajouté !`, 'succes');
    document.getElementById('nomClient').value   = '';
    document.getElementById('nbArticles').value  = '';
    rafraichir();
  } catch (e) { afficherMessage('Erreur serveur', 'erreur'); }
}

// Servir un client
async function servirClient() {
  const numero = parseInt(document.getElementById('numeroCaisse').value);
  if (isNaN(numero)) { afficherMessage('Indique un numéro de caisse !', 'erreur'); return; }
  try {
    const res  = await fetch(`${API}/caisse/servir`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ numero })
    });
    const data = await res.json();
    if (data.erreur) { afficherMessage(data.erreur, 'erreur'); return; }
    afficherMessage(`Client servi à la caisse ${numero} !`, 'succes');
    rafraichir();
  } catch (e) { afficherMessage('Erreur serveur', 'erreur'); }
}

// Ouvrir une caisse
async function ouvrirCaisse() {
  const numero = parseInt(document.getElementById('numeroCaisse').value);
  if (isNaN(numero)) { afficherMessage('Indique un numéro de caisse !', 'erreur'); return; }
  try {
    const res  = await fetch(`${API}/caisse/ouvrir`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ numero })
    });
    const data = await res.json();
    if (data.erreur) { afficherMessage(data.erreur, 'erreur'); return; }
    afficherMessage(`Caisse ${numero} ouverte !`, 'succes');
    rafraichir();
  } catch (e) { afficherMessage('Erreur serveur', 'erreur'); }
}

// Fermer une caisse
async function fermerCaisse() {
  const numero = parseInt(document.getElementById('numeroCaisse').value);
  if (isNaN(numero)) { afficherMessage('Indique un numéro de caisse !', 'erreur'); return; }
  try {
    const res  = await fetch(`${API}/caisse/fermer`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ numero })
    });
    const data = await res.json();
    if (data.erreur) { afficherMessage(data.erreur, 'erreur'); return; }
    afficherMessage(`Caisse ${numero} fermée !`, 'succes');
    rafraichir();
  } catch (e) { afficherMessage('Erreur serveur', 'erreur'); }
}

async function rafraichirHistorique() {
    const res = await fetch('http://localhost:8080/api/historique');
    const data = await res.json();
    const liste = document.getElementById('liste-historique');
    liste.innerHTML = '';
    [...data].reverse().forEach(e => {
        const li = document.createElement('li');
        li.textContent = `[${e.heure}] ${e.nom} — ${e.articles} articles → Caisse ${e.caisse}`;
        liste.appendChild(li);
    });
}

setInterval(rafraichirHistorique, 3000);
rafraichirHistorique();

// Rafraîchissement automatique toutes les 3 secondes
setInterval(rafraichir, 3000);
rafraichir();