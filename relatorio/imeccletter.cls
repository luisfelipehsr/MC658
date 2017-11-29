%%% imeccletter.cls

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{imeccletter}[2011/09/30 Document class for letters with header and footer]

\RequirePackage{ifthen}
\RequirePackage{geometry}
\RequirePackage{unicamplogo}
\RequirePackage{imecclogo}

%\DeclareOption*{\PassOptionsToClass{\CurrentOption}{letter}}
\ProcessOptions
\LoadClassWithOptions{letter}

\geometry{left=3cm,right=2cm,top=1cm,bottom=1cm}
\geometry{includehead=true,includefoot=true}
\geometry{headheight=50pt}
\geometry{headsep=8pt}

\DeclareFixedFont{\headerfonti}{\encodingdefault}{\sfdefault}{\bfdefault}{\updefault}{12}
\DeclareFixedFont{\headerfontii}{\encodingdefault}{\sfdefault}{\bfdefault}{\updefault}{12}
\DeclareFixedFont{\headerfontiii}{\encodingdefault}{\sfdefault}{\bfdefault}{\updefault}{12}
\DeclareFixedFont{\footerfonti}{\encodingdefault}{\sfdefault}{\mddefault}{\updefault}{8}

\newcommand{\department}[1]{\def\thedepartment{#1}}
\department{}
\newcommand{\fax}[1]{\def\faxnum{#1}}
\fax{}
\newcommand{\email}[1]{\def\theemail{#1}}

\def\ps@firstpage{%
     \def\@oddhead{%
\bgroup
\fontsize{10pt}{12pt}\selectfont
\begin{tabular*}{\textwidth}[t]{@{}l@{\hspace*{1ex}}l@{\hspace*{1em}}@{}l@{}}
  \unicamplogol[small] & \imecclogo &
  \begin{tabular}[b]{@{}l@{}}
    \mbox{\headerfonti \MakeUppercase{Universidade Estadual de Campinas}}\\
    \mbox{\headerfontii Instituto de Matem\'atica, Estat\'{\i}stica e Computa\c{c}\~ao Cient\'{\i}fica}\\
    \mbox{\headerfontiii \thedepartment}
  \end{tabular} \\\hline
\end{tabular*}
\egroup}
     \ifx\fromaddress\@empty\def\@oddfoot{}\else
     \def\@oddfoot{%
        {\footerfonti\begin{tabular*}{\textwidth}{@{}l@{}}\hline\ignorespaces
        \fromaddress\end{tabular*}}}\fi}

\renewcommand*{\opening}[1]{%
    \thispagestyle{firstpage}%
    {\raggedleft\begin{tabular}{l@{}}\ignorespaces
      \ifx\@empty\fromlocation\else\fromlocation, \fi\@date \end{tabular}\par}%
  \vspace{2\parskip}%
  {\raggedright \toname \\ \toaddress \par}%
  \vspace{2\parskip}%
  #1\par\nobreak}

\longindentation=.625\textwidth
\renewcommand{\closing}[1]{\par\nobreak\vspace{\parskip}%
  \stopbreaks
  \noindent
%  \ifx\@empty\fromaddress\else
  \hspace*{\longindentation}%\fi
  \parbox{\indentedwidth}{\raggedright
       \ignorespaces #1\\[6\medskipamount]%
       \ifx\@empty\fromsig
           \fromname
       \else \fromsig \fi\strut}%
   \par}

\location{Campinas}
\address{Rua S\'ergio Buarque de Holanda, 651 -- Cidade Universit\'aria ``Zeferino Vaz'' -- Distr. Barão Geraldo -- Campinas -- SP\\
          CEP 13083-859 
          \ifx\telephonenum\@empty\else\ -- Tel.\ \telephonenum\fi%
          \ifx\faxnum\@empty\else\ -- FAX \faxnum\fi%
          \ifx\theemail\@empty\else\ -- Email: \theemail\fi%
}
\endinput
