1) Décompressez l'archive OpenAL-1.1.rar à la racine du dépot, si vous utilisez Mingw ou Visual Studio. Sinon, allez vous cherchez une bonne corde de chanvre bien solide et un tabouret instable.
2) Installez OpenAl en copiant les includes et les libs dans les bons dossiers de votre compilateur (pensez à faire la distinction 32/64bits)
3) Dans le SDK téléchargé depuis le site, dans le redist se trouve un installeur, qui sert "à faire fonctionner OpenAL sur d'autres ordinateurs". En pratique, il se contente d'extraire plusieurs DLL de manière très crade directement dans System32. Aussi, ne le lancez pas, j'ai placé une version compressée de ces DLLs dans une archive du dépot.
4) Décompressez l'archive ALUT à la base du dépot
5) Installez ALUT - la DLL est déjà dans l'archive avec celles d'OpenAL
6) Priez un bon coup, et essayez de compiller...


Je dois avouer que j'en ai chier des briques pour pouvoir enfin compiler. Le SVN d'OpenAL est mort, ils demandent d'utiliser cmake pour compiler les sources mais ce dernier déclare rapidement forfait, et seules les binaires pour Visual Studio sont fournis pour Windows.
Au final, j'ai utilisé l'outil reimp (que je ne connaissais pas jusque là) de la Mingw Tool Suite, qui sert à transformer les bibliothèques binaires format MS au format GCC. Peu bavard mais très pratique, je sens que ce petit logiciel va être encore très utile dans le futur...