  filetype on
  filetype plugin on
  filetype plugin indent on
  syntax on

" Some useful settings
  set smartindent
  set expandtab         "tab to spaces
  set tabstop=4         "the width of a tab
  set shiftwidth=4      "the width for indent
 " set foldenable
  set foldmethod=indent "folding by indent
  set ignorecase        "ignore the case when search texts
  set incsearch
  set relativenumber "line number
  set cursorline       "hilight the line of the cursor
  set nowrap           "no line wrapping
  set number

  :autocmd BufNewFile *.cpp 0r ~/.temp.temp
  map<F5> :w <CR> : ! g++ -std=c++17 % &&  ./a.out <CR>
