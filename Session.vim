let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/of_v0.10.1_linux64gcc6_release/apps/myApps/rosendal
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 src/ofApp.h
badd +1 src/ofApp.cpp
badd +1 ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.h
badd +217 ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.cpp
badd +24 ../../../addons/ofxBullet/src/shapes/ofxBulletCustomShape.h
badd +1 src/Player.h
badd +7 src/Player.cpp
badd +1 make:\ \*\*\*\ \[/home/ask/Development/of_v0.10.0_linux64gcc6_release/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk
badd +1 bin/data/shaders/shader.frag
badd +1 bin/data/shaders/shader.vert
badd +1 src/main.cpp
badd +1 bin/data/shaders/noise.frag
badd +1 bin/data/shaders/noise.vert
argglobal
silent! argdel *
$argadd src/ofApp.h
set stal=2
tabnew
tabnew
tabnew
tabnext -3
edit src/main.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 10 - ((9 * winheight(0) + 53) / 106)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
10
normal! 0
tabnext
edit src/ofApp.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 146 + 149) / 299)
exe 'vert 2resize ' . ((&columns * 152 + 149) / 299)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
argglobal
if bufexists('src/ofApp.h') | buffer src/ofApp.h | else | edit src/ofApp.h | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 146 + 149) / 299)
exe 'vert 2resize ' . ((&columns * 152 + 149) / 299)
tabnext
edit src/Player.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 148 + 149) / 299)
exe 'vert 2resize ' . ((&columns * 150 + 149) / 299)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 8 - ((7 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
8
normal! 0
wincmd w
argglobal
if bufexists('src/Player.h') | buffer src/Player.h | else | edit src/Player.h | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 148 + 149) / 299)
exe 'vert 2resize ' . ((&columns * 150 + 149) / 299)
tabnext
edit bin/data/shaders/noise.frag
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 149 + 149) / 299)
exe 'vert 2resize ' . ((&columns * 149 + 149) / 299)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 010|
wincmd w
argglobal
if bufexists('bin/data/shaders/noise.vert') | buffer bin/data/shaders/noise.vert | else | edit bin/data/shaders/noise.vert | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 149 + 149) / 299)
exe 'vert 2resize ' . ((&columns * 149 + 149) / 299)
tabnext 3
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
set winminheight=1 winminwidth=1
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
