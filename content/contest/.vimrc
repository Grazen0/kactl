set nocp cul et hls ic is nu rnu sw=4 ts=4 scs mouse=a ttm=100 ve=all noswf
filetype plugin indent on
syn on
nn <esc> :noh<cr>
nn U <c-r>
no gh ^
no gl $
nn <f9> :w<cr>:!g++ -std=c++23 -g -fsanitize=undefined,address "%" && ./a.out < "%:r.in"<cr>
nn <f10> :e %:r.in<cr>
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
colo evening

