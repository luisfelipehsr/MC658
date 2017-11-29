%%% imeccexam.cls

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{imeccexam}[2011/01/31 IMECC Exam template]

\LoadClassWithOptions{article}

\RequirePackage{ifthen}
\RequirePackage{fancyhdr}
\RequirePackage{enumerate}
\RequirePackage{geometry}
\RequirePackage{totpages}
\RequirePackage{unicamplogo}
\RequirePackage{imecclogo}

\newboolean{onequestionperpagebool} \setboolean{onequestionperpagebool}{false}
\newboolean{noblankpagesbool} \setboolean{noblankpagesbool}{false}
\newboolean{noscoretablebool} \setboolean{noscoretablebool}{false}
\newboolean{multiplechoicebool} \setboolean{multiplechoicebool}{false}
\DeclareOption{onequestionperpage}{\setboolean{onequestionperpagebool}{true}}
\DeclareOption{noblankpages}{\setboolean{noblankpagesbool}{true}\setboolean{onequestionperpagebool}{false}}
\DeclareOption{noscoretable}{\setboolean{noscoretablebool}{true}}
\DeclareOption{multiplechoice}{\setboolean{multiplechoicebool}{true}\setboolean{noscoretablebool}{true}}
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
\ProcessOptions\relax
\PassOptionsToClass{a4paper}{article}

\geometry{left=2cm,right=3cm,top=1cm,bottom=1cm}
\geometry{includehead=true,includefoot=false}
\geometry{headheight=50pt}
\geometry{headsep=8pt}

\AtEndDocument{\ifthenelse{\boolean{onequestionperpagebool}}{}{\finishfirstpage}\ifthenelse{\boolean{noblankpagesbool}}{}{\addblankpages{\value{blankpagescounter}}}}

\newcommand{\goodluck}{Boa Prova!}

\newcounter{questionnumber} \setcounter{questionnumber}{0}
\newcounter{numberofquestions} \setcounter{numberofquestions}{0}
\newcounter{blankpagescounter}
\newcounter{internalblankpagescounter}

\setlength{\marginparsep}{1mm}
\DeclareFixedFont{\headerfonti}{\encodingdefault}{\sfdefault}{\bfdefault}{\updefault}{12}
\DeclareFixedFont{\headerfontii}{\encodingdefault}{\sfdefault}{\bfdefault}{\updefault}{12}
\DeclareFixedFont{\headerfontiii}{\encodingdefault}{\sfdefault}{\bfdefault}{\updefault}{12}
\DeclareFixedFont{\footerfonti}{\encodingdefault}{\sfdefault}{\mddefault}{\updefault}{8}
\DeclareFixedFont{\topmatterboldfont}{\encodingdefault}{\sfdefault}{\bfdefault}{\updefault}{10}

% first page style
\fancypagestyle{imeccexamfirstpage}{%
%\renewcommand{\footrulewidth}{\headrulewidth}
\fancyhf{} \fancyhead{} \fancyhead[L]{
\bgroup
\begin{tabular}[t]{@{\ }l@{\ }l@{\ }l}
  \unicamplogol[small] % \\
&
  \imecclogo
&
  \begin{tabular}[b]{@{}l}
    \mbox{\headerfonti \MakeUppercase{UNIVERSIDADE ESTADUAL DE CAMPINAS}}\\
%    \mbox{\headerfontii \thedivision{\header@language}} \\
    \mbox{\headerfontii Instituto de Matem\'atica, Estat\'{\i}stica e Computa\c{c}\~ao Cient\'{\i}fica}\\
%    \mbox{\headerfontiii MA-141 GEOMETRIA ANAL\'ITICA E VETORES}
    \mbox{\headerfontii\@examtitle}
  \end{tabular}
\end{tabular}
\egroup
}
%\fancyfoot{}
%\fancyfoot[L]{%
%\bgroup\fontsize{8pt}{10pt}\selectfont\footerfonti
%\begin{tabular}{@{}l@{}l}
%  \theorgaddress\ -- \theorgaddresscompl\ -- \theorgaddressarea\ -- \theorgaddresscity\ --
%  \thezipcodelabel\ \thezipcode\\
%  \ifx\thetelephone\@empty\else \thetelephonelabel:\ \thetelephone\fi%
%  \ifx\thefax\@empty\else\ -- \thefaxlabel:\ \thefax\fi%
%  \ifx\theemail\@empty\else\ -- \theemaillabel:\ \theemail\fi\ ~
%\end{tabular}
%\egroup
%}
}
\AtBeginDocument{\thispagestyle{imeccexamfirstpage}\firstpagetopmatter}

% other pages style (default)
\fancypagestyle{imeccexamotherpage}{%
\fancyhf{} \fancyhead{} \fancyhead[L]{%
\bgroup
%\fontsize{10pt}{12pt}\selectfont\sffamily
\headerfontii\mbox{\@examtitle}\hfill \thepage/\ref{TotPages}
\egroup
}}
\pagestyle{imeccexamotherpage}

% top matter
% - title
\def\@examtitle{\mbox{}}
\newcommand{\examtitle}[1]{\def\@examtitle{#1}}

% - score table
\newcounter{argptrows}\setcounter{argptrows}{0}
\def\@scoretablerows{}
\def\set@scoretablerows{\addtocounter{argptrows}{1}\def\@scoretablerows{
\raisebox{-2mm}{\fontsize{10pt}{12pt}\selectfont\sffamily Q\the\value{argptrows}}&\hspace*{5mm}\\[1ex]\hline}}

% - multiple choice answer table

\newcommand{\firstpagetopmatter}{%
\bgroup
\fontsize{10pt}{12pt}\selectfont
\noindent\begin{tabular}{|p{12cm}|p{3.75cm}|}
\hline
\fontsize{10pt}{12pt}\selectfont\sffamily ALUNO &
\fontsize{10pt}{12pt}\selectfont\sffamily RA \\
\ & \ \\ \hline
\end{tabular}
\par
\ifthenelse{\boolean{noscoretablebool}}{}{\marginpar{\raisebox{23mm}[0pt][0pt]{%
\begin{tabular}[t]{|@{\hspace*{1mm}}l@{\hspace*{1mm}}|l|} \hline
\whiledo{\value{argptrows}<\value{numberofquestions}}{\set@scoretablerows\@scoretablerows}
\fontsize{10pt}{12pt}\selectfont $\sum$ & \\[1ex] \hline
\end{tabular}}}}
\par
\begin{center} \sffamily\bfseries\large\mbox{\@examtitle} \end{center}
\egroup}

% instructions
\newenvironment{instructions}{\bigskip\begin{center}\fontsize{10pt}{12pt}\selectfont\sffamily\textbf{INSTRU\c{C}\~OES}\\[1em]\begin{minipage}{14cm}}{\end{minipage}\end{center}\bigskip}

% questions

\newenvironment{question}[1][1]{%
\addtocounter{blankpagescounter}{#1}\stepcounter{questionnumber}%
\ifthenelse{\boolean{onequestionperpagebool}}{%
    \ifthenelse{\value{questionnumber}=1}{\finishfirstpage}{}}{}%
    \begin{minipage}{15.8cm}\noindent\textbf{Quest\~ao \arabic{questionnumber}. }}{%
\end{minipage}\ifthenelse{\boolean{onequestionperpagebool}}{%
    \addblankpages{\value{blankpagescounter}\setcounter{blankpagescounter}{0}}}{\medskip}}

\newenvironment{questionitems}{\begin{enumerate}[(a)]}{\end{enumerate}}

\newcommand{\setnumberofquestions}[1]{\setcounter{numberofquestions}{#1}}

% blank pages
\newcommand{\finishfirstpage}{\null\vfill\centerline{\goodluck}\newpage}
\newcommand{\addblankpages}[1]{%
%    \ifthenelse{\boolean{onequestionperpagebool}}{\finishfirstpage}{}%
\setcounter{internalblankpagescounter}{#1}
\whiledo{\value{internalblankpagescounter} > 0}{\null\newpage\addtocounter{internalblankpagescounter}{-1}}\setcounter{internalblankpagescounter}{0}}

\newcommand{\addfinalblankpages}{%
  \ifthenelse{\value{noblankpages}}{}{
    \ifthenelse{\value{onequestionperpagebool}}{\addblankpages{\value{blankpagescounter}}}{}}}

\AtEndDocument{\immediate\write\@auxout{\string\setnumberofquestions{\the\value{questionnumber}}}}
\endinput
