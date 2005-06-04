;; .emacs
;;; Initialization file for GNU emacs.
;;; James Larus, 1985.


(setq load-path (append (list "~/Lib/Emacs") load-path))


;;; Define some new commands and bind them.

(defun two-pane-window ()
  "Make the current window into a two pane window."
  (delete-other-windows)
  (split-window-vertically))
(global-set-key "\^x@" 'two-pane-window)


(defun to-shell (arg)
  (interactive "P")
  (let ((current-file-name (buffer-file-name)))
    (if (get-buffer-process (get-buffer "*shell*"))
	(pop-to-buffer "*shell*")
	(shell))
    (if (and arg current-file-name)
	(insert (format "pushd %s" (file-name-directory current-file-name))))))

(global-set-key "\^x!" 'to-shell)


(defun join-lines ()
  "Join current line and next line."
  (interactive "")
  (delete-indentation 1))
(global-set-key "\eJ" 'join-lines)


(defun move-to-first-line ()
  "Place cursor on first line of window."
  (interactive "")
  (move-to-window-line 0))


(defun move-to-last-line ()
  "Place cursor on last line of window."
  (interactive "")
  (move-to-window-line -1))


(defun my-kill-line (arg)
  "Smarter kill-line."
  (interactive "P")
  (if (and (null arg) (bolp))
      (kill-line 1)
      (kill-line arg)))
(global-set-key "\^k" 'my-kill-line)


(defun my-beginning-of-line (arg)
  "Smarter begining-of-line."
  (interactive "p")
  (if (bolp)
      (while (looking-at "[ \t]") (forward-char))
      (beginning-of-line arg)))
(global-set-key "\^a" 'my-beginning-of-line)


(defun line-to-top-of-window ()
  "Position current line at top of window"
  (interactive)
  (recenter 0))
(global-set-key "\e!" 'line-to-top-of-window)


(defun recenter-to-top ()
  "Position current defun at top of window"
  (interactive)
  (beginning-of-defun)
  (recenter 0))
(global-set-key "\e#" 'recenter-to-top)


(defun toggle-trace ()
  (interactive)
  (setq stack-trace-on-error (not stack-trace-on-error)))


(defun uw-address (&optional arg)
  "Insert address of CS Dept.  With argument, insert user's name first."
  (interactive "P")
  (if arg (insert (format "%s\n" (user-full-name))))
  (push-mark (point) nil)
  (insert "Computer Sciences Department\nUniversity of Wisconsin\n1210 West Dayton Street\nMadison, WI 53706\nlarus@cs.wisc.edu\nhttp://www.cs.wisc.edu/~larus\n608-262-9519\n"))


(defun msr-address (&optional arg)
  "Insert address of MSR.  With argument, insert user's name first."
  (interactive "P")
  (if arg (insert "James R. Larus\n"))
  (push-mark (point) nil)
  (insert "Microsoft Research\nOne Microsoft Way\nRedmond, WA 98052\nlarus@microsoft.com\nhttp://www.research.microsoft.com/~larus\n425-936-2981\n"))


(defun save-buffers-kill-emacs (&optional arg)
  "Offer to save each buffer, then kill this Emacs fork."
  (interactive "P")
  (save-some-buffers arg)
  (kill-emacs arg))


(defun buffers-revert ()
  "Revert all buffers."
  (interactive)
  (save-some-buffers)
  (let ((buffers (buffer-list)))
    (while buffers
      (if (buffer-file-name (car buffers))
	  (save-excursion
	    (message "Reverting %s..." (buffer-name (car buffers)))
	    (set-buffer (car buffers))
	    (revert-buffer t t)
	    (message "Reverting %s...done" (buffer-name (car buffers)))))
      (setq buffers (cdr buffers)))))


(defvar grammar-list '("\\ba[
][aeiou]"
		       "\\bso\\bthat"
		       ",\\bthen\\b"))

(defun check-grammar ()
  "Check common grammar mistakes."
  (interactive)
  (let ((s grammar-list))
    (while s
      (goto-char (point-min))
      (while (re-search-forward (car s) nil t)
	(recursive-edit))
      (setq s (cdr s)))))


(defun find-duplicated-words ()
  "Find the next pair of contiguous words that are identical."
  (interactive)
  (while (re-search-forward "\\b\\([a-zA-Z-][a-zA-Z-]\\w*\\)\\b" nil t)
    (let ((word (buffer-substring (match-beginning 1) (match-end 1))))
      (while (looking-at "[ \t\n]") (forward-char 1))
      (if (looking-at (format "%s\\b" word))
	  (error "Duplicated word: '%s'" word))))
  (message "Done"))


(defun tags-arguments ()
  "Display the argument list of a function in the TAGS file."
  (interactive)
  (save-window-excursion
    (call-interactively 'find-tag)
    (let ((point (point)))
      (end-of-line)
      (message (buffer-substring point (point))))))


(defun enscript-buffer ()
  "Print the current buffer 2-to-a-page."
  (interactive)
  (shell-command-on-region (point-min) (point-max) "enscript -2rG" nil))


(defun deslime ()
  "Transform the current buffer from a Symbolics formatted file into an
ascii file."
  (interactive)
  (save-excursion
    (let ((original-size (buffer-size)))
      (goto-char (point-min))
      (message "Removing unnecessary white space...")
      (replace-regexp "[ 	]+$" "")
      ;(tabify (point-min) (point-max))
      (message "Removing unnecessary white space...done")
      (let* ((new-size (buffer-size))
	     (shrinkage (- original-size new-size)))
	(message (format "Buffer size: %d -> %d (-%d chars, %d percent)"
			 original-size
			 new-size
			 shrinkage
			 (/ (* 100 shrinkage) original-size)))))))



;;; Hooks to customize various modes.

(setq bibtex-mode-hook
      (function (lambda ()
	(auto-fill-mode 1)
	(setq bibtex-hardcopy "dvipr")
	(setq bibtex-field-indent 4)
	(setq bibtex-field-use-quotes t)
	(setq bibtex-abbrev-fields (cons "YEAR" bibtex-abbrev-fields))
	(setq bibtex-abbrev-files '("abbrev"))
	(let ((x bibtex-entry-specs))
	  (while x
	    (fix-bibtex-spec (car x) (list "ABSTRACT" "WHERE"))
	    (setq x (cdr x)))))))


(defun fix-bibtex-spec (spec new-fields)
  ;; Add a list of new fields onto the end of a BibTeX specification.
  (cond ((null (cdr spec))
	 (let ((x (car spec)))
	   (while (and (cdr x) (not (equal x new-fields)))
	     (setq x (cdr x)))
	   (if (not (equal x new-fields)) ; Don't add twice!
	       (rplacd x new-fields))))
	(t (fix-bibtex-spec (cdr spec) new-fields))))


					;;; Use cc-mode not c-mode/c++-mode

(setq-default fill-column 76)

(setq lisp-mode-hook
      (setq emacs-lisp-mode-hook
	    (list (function (lambda ()
		    (local-set-key "\^h" 'backward-delete-char-untabify)
		    (local-unset-key "\^z")
		    (local-unset-key "\^c\^z")
		    (put 'defconstructor 'lisp-indent-hook 3)))
		  ;'invoke-common-lisp-mode
		  )))
(autoload 'common-lisp-mode "cl" "Common Lisp Mode extensions" t)
(autoload 'invoke-common-lisp-mode "cl" "Common Lisp Mode extensions" t)


(setq mh-folder-mode-hook
      (function (lambda ()
		  ;(setq mh-lpr-command-format "lpr -h") ; No title page!
		  ;(setq mh-rejected-letter-start
			"\\(^   ----- Unsent message follows -----$\\)\\|\\(^------- Unsent Draft$\\)")
		  (local-set-key "\^h" 'mh-previous-page)))


(setq mh-letter-mode-hook
      (function (lambda ()
		  (auto-fill-mode 1)
		  (setq adaptive-fill-mode nil))))


(setq tex-mode-hook
      (function (lambda ()
		  (setq tex-delimiters-semi '(("{\\em " "\\/}" "em" "e")))
		  (setq tex-hsl-default "~/.spell-excp.hsl")
		  (setq tex-usl-default "~/.spell-excp.usl")
		  (auto-fill-mode 1)
		  (abbrev-mode 1))))


(setq dired-mode-hook
      (function (lambda ()
		  (define-key dired-mode-map "l" 'dired-list-file)
		  (define-key dired-mode-map "s" 'dired-sort-by-date))))


(setq mh-recursive-folders t)


(defun dired-list-file ()
  "In dired, print the file named on this line."
  (interactive)
  (apply 'call-process
	 (append (list "lpr" "" nil nil)
		 lpr-switches
		 (list (dired-get-filename)))))


(defun dired-sort-by-date ()
  "Produce a listing sorted by date of modification."
  (interactive)
  (let ((dired-listing-switches (concat dired-listing-switches "t")))
    (revert-buffer)))


;;; From: Alan Stebbens <aks%nowhere@hub.ucsb.edu>

(defun z-mode () "\
Temporary major mode triggered by the \".Z\" suffix on a file,
used to automatically uncompress the file when visiting.  After
running the buffer contents through \"uncompress\", the buffer
name is changed by truncating the \".Z\" (as well as the visited
file name).  Also, the buffer is marked as read-only.  Finally,
normal-mode is invoked to process the buffer for its normal mode."
  (if (and (not (null buffer-file-name))
	   (string-match "^\\(.*\\)\\.Z$" buffer-file-name))
      (let ((new-name (substring buffer-file-name
				 (match-beginning 1)
				 (match-end 1)))
	    (buffer-read-only nil))
	(message "Uncompressing text...")
	(shell-command-on-region (point-min) (point-max) "uncompress" t)
	(message "Uncompressing text...done")
	(goto-char (point-min))
	(set-visited-file-name new-name)
	(set-buffer-modified-p nil)))
  (normal-mode))

(defun gzip-mode () "\
Temporary major mode triggered by the \".gz\" suffix on a file,
used to automatically uncompress the file when visiting.  After
running the buffer contents through \"gzip -d\", the buffer
name is changed by truncating the \".gz\" (as well as the visited
file name).  Also, the buffer is marked as read-only.  Finally,
normal-mode is invoked to process the buffer for its normal mode."
  (if (and (not (null buffer-file-name))
	   (string-match "^\\(.*\\)\\.gz$" buffer-file-name))
      (let ((new-name (substring buffer-file-name
				 (match-beginning 1)
				 (match-end 1)))
	    (buffer-read-only nil))
	(message "Uncompressing text...")
	(shell-command-on-region (point-min) (point-max) "gzip -d" t)
	(message "Uncompressing text...done")
	(goto-char (point-min))
	(set-visited-file-name new-name)
	(set-buffer-modified-p nil)))
  (normal-mode))



(defun sort-mailing-list ()
  (interactive)
  (require 'sort)
  (sort-subr nil
	     '(lambda () (if (not (eobp)) (forward-char 1)))
	     'forward-paragraph
	     '(lambda () (end-of-line) (backward-word 1) nil)
	     'end-of-line))



;;; Change emacs environment.

;;; Rebind commands.

(global-set-key "\^h" 'delete-backward-char)
(global-set-key "\^x?" 'help-command)
(global-set-key "\^x\^v" 'find-file-other-window)
(global-set-key "\eG" 'goto-line)
(global-set-key "\^xC" 'compile)
(global-set-key "\^x\^p" 'switch-to-buffer-other-window)

(setq transient-mark-mode t)


;;; Use mh-e to read mail.

(autoload 'mh-rmail "mh-e")
(global-set-key "\^xr" 'mh-rmail)
(autoload 'mh-smail "mh-e")
(global-set-key "\^xm" 'mh-smail)
(setq mh-lpr-command-format "enscript -2r -")


;;; Use Peehong's TeX  mode.

(autoload 'tex-mode "TeX-mode" "" t)
(autoload 'bibtex-mode "BibTeX-mode" "" t)

(autoload  'crypt-mode "crypt-mode" "" t)


(setq auto-mode-alist
      (append (list (cons "\\.sty" 'tex-mode)
		    (cons "\\.bbl" 'tex-mode)
		    (cons "\\.bib$" 'bibtex-mode)
		    (cons "\\.cl$" 'lisp-mode)
		    (cons "\\.x$"  'crypt-mode)
		    (cons "\\.Z$"  'z-mode)
		    (cons "\\.gz$" 'gzip-mode))
	      auto-mode-alist))


(setq completion-ignored-extensions
      (cons "ibbl" (cons ".fasl" completion-ignored-extensions)))


;;; Perl mode

(autoload 'perl-mode "perl-mode")

(setq auto-mode-alist (append (list (cons "\\.pl" 'perl-mode))
			      auto-mode-alist))

(setq perl-mode-hook (function
		      (lambda ()
		       (setq perl-indent-level 2)
		       (setq perl-continued-statement-offset 2)
		       (setq perl-continued-brace-offset 0)
		       (setq perl-brace-offset 2)
		       (setq perl-brace-imaginary-offset 0)
		       (setq perl-label-offset -2))))


;;; Nroff mode

(autoload 'nroff-mode "nroff-mode")

(setq auto-mode-alist (append (list (cons "\\.me" 'nroff-mode)
				    (cons "\\.ms" 'nroff-mode)
				    (cons "\\.nr" 'nroff-mode)
				    (cons "\\.tr" 'nroff-mode))
			      auto-mode-alist))

(setq nroff-mode-hook (function
		       (lambda ()
			(auto-fill-mode 1))))




;;; Change Log mode

(setq change-log-mode-hook (function
			    (lambda ()
			      (auto-fill-mode 1))))

;;; ML:

(autoload 'sml-mode "sml-mode" "Major mode for editing ML programs." t)
(autoload 'sml "sml-proc" "Run an inferior ML process." t)

(setq auto-mode-alist (append '(("\\.sml$" . sml-mode)
				("\\.ML$"  . sml-mode)) auto-mode-alist))

(defconst sml-font-lock-keywords (purecopy
  (list
   '("^[ \t]*\\(fun\\|val\\|and\\|let\\|type\\|datatype\\exception\\)\\>[ \t]*\\(\\sw+\\)?"
     2 font-lock-function-name-face t)
   (cons (concat "\\<\\(int\\|bool\\|string\\)\\>")
	 'font-lock-type-face)
   (list (concat "\\<\\("
		 "abstype\\|and\\|andalso\\|as\\|case\\|datatype\\|do\\|else\\|"
		 "end\\|eqtype\\|exception\\|fn\\|fun\\|functor\\|handle\\|"
		 "if\\|in\\|include\\|infix\\|infixr\\|let\\|local\\|nofix\\|"
		 "of\\|op\\|open\\|orelse\\|raise\\|rec\\|sharing\\|sig\\|"
		 "signature\\|struct\\|structure\\|then\\|type\\|val\\|while\\|"
		 "with\\|withtype"
		 "\\)\\>")
	 1 'font-lock-keyword-face)))
  "Expressions to highlight in SML mode.")


;;; Disable angl-ftp

(defun delete-cdr (elt lst)
  (cond ((null lst)
	 nil)
	((equal elt (cdr (car lst)))
	 (delete-cdr elt (cdr lst)))
	(t
	 (cons (car lst) (delete-cdr elt (cdr lst))))))

(setq file-name-handler-alist (delete-cdr 'ange-ftp-hook-function
					   file-name-handler-alist))

(setq file-name-handler-alist (delete-cdr 'ange-ftp-completion-hook-function
					   file-name-handler-alist))

;;; Highlight mode

(cond ((string-match "XEmacs\\|Lucid" emacs-version)
       (require 'cc-mode)
       (c-set-offset 'inline-open 0)
       (define-key c-mode-map "\eq"   'c-fill-paragraph)

       (set-specifier default-toolbar-visible-p nil)

       (setq font-lock-use-maximal-decoration t)
       (setq font-lock-use-fonts t)
       (setq font-lock-use-colors t)
       (require 'font-lock)

       (set-face-foreground 'font-lock-comment-face "light sea green")
       (make-face-italic 'font-lock-comment-face)
       (make-face-bold 'font-lock-comment-face)
       (set-face-foreground 'font-lock-function-name-face "orange red")
       (make-face-bold 'font-lock-function-name-face)
       (set-face-foreground 'font-lock-string-face "light slate grey")
       (make-face-unitalic 'font-lock-string-face)
       (set-face-foreground 'font-lock-keyword-face "blue")
       (make-face-bold 'font-lock-keyword-face)

       (set-face-foreground 'font-lock-comment-face "blue")
       (set-face-font 'font-lock-comment-face "-*-Lucida-Bold-I-*-*-*-120-*-*-*-*-ISO8859-1")
       (set-face-foreground 'font-lock-string-face "light slate grey")
       (set-face-font 'font-lock-string-face "-*-LucidaTypewriter-Bold-R-*-*-*-120-*-*-*-*-ISO8859-1")
       (set-face-foreground 'font-lock-doc-string-face "green4")
       (set-face-font 'font-lock-doc-string-face "-*-LucidaTypewriter-Bold-R-*-*-*-120-*-*-*-*-ISO8859-1")
       (set-face-foreground 'font-lock-function-name-face "red")
       (set-face-font 'font-lock-function-name-face "-*-LucidaTypewriter-Bold-R-*-*-*-120-*-*-*-*-ISO8859-1")
       (set-face-foreground 'font-lock-keyword-face "blue")
       (set-face-font 'font-lock-keyword-face "-*-LucidaTypewriter-Bold-R-*-*-*-120-*-*-*-*-ISO8859-1")
       (set-face-foreground 'font-lock-type-face "blue")
       (set-face-font 'font-lock-type-face "-*-LucidaTypewriter-Bold-R-*-*-*-120-*-*-*-*-ISO8859-1")

       (add-hook 'emacs-lisp-mode-hook	'turn-on-font-lock)
       (add-hook 'lisp-mode-hook	'turn-on-font-lock)
       (add-hook 'c-mode-hook		'turn-on-font-lock)
       (add-hook 'c++-mode-hook		'turn-on-font-lock)
       (add-hook 'perl-mode-hook	'turn-on-font-lock)
       (add-hook 'tex-mode-hook		'turn-on-font-lock)
       (add-hook 'texinfo-mode-hook	'turn-on-font-lock)
       (add-hook 'postscript-mode-hook	'turn-on-font-lock)
       (add-hook 'dired-mode-hook	'turn-on-font-lock)
       (add-hook 'ada-mode-hook		'turn-on-font-lock)
       (add-hook 'compilation-mode-hook	'turn-on-font-lock)

       ;; mh-e stuff
       (setq toolbar-mail-command 'mh-rmail)
       (defvar mh-font-keywords
	 '(("\\(^From:.*\\)" 1 font-lock-function-name-face t)
	   ("\\(^To:.*\\)" 1 font-lock-function-name-face t)
	   ("\\(^Subject:.*\\)" 1 font-lock-function-name-face t)
	   ("\\(^[a-zZ-Z-]+:.*\\)" 1 font-lock-keyword-face t))
	 "mh-e additions for font-lock-keywords.")

       (defun mh-show-mode-font-hook ()
	 "Hook to turn on and customize fonts."
	 (make-local-variable 'font-lock-mode-hook)
	 (add-hook 'font-lock-mode-hook	; set a hook with inline function
		   (function		; modifies font-lock-keywords when
		    (lambda ()		; font-lock-mode run
		      (setq font-lock-keywords
			    (append mh-font-keywords font-lock-keywords)))))
	 (font-lock-mode 1))

       (add-hook 'mh-show-mode-hook 'mh-show-mode-font-hook)

       (require 'func-menu)
       (define-key global-map 'f8 'function-menu)
       (add-hook 'find-file-hooks 'fume-add-menubar-entry)
       (define-key global-map "\C-cg" 'fume-prompt-function-goto)
       (define-key global-map '(shift button3) 'mouse-function-menu)

       (setq find-file-compare-truenames t)

       (setq frame-title-format (concat (getenv "HOSTNAME")
					": "
					frame-title-format))
       (setq frame-icon-title-format (concat (getenv "HOSTNAME") ": %b")))

      (window-system
       (setq hilit-mode-enable-list  nil ;'(not text-mode)
             hilit-background-mode   'light
             hilit-inhibit-hooks     nil
             hilit-inhibit-rebinding nil)
       (set-default 'hilit-auto-rehighlight t)
       (require 'hilit19)
       (setq find-file-existing-other-name t)
       (if (eq window-system 'w32)
	   (let ()
	     (set-default-font
	      "-*-Lucida Console-bold-r-*-*-14-120-*-*-c-*-*-ansi-")
	     ;(setq directory-sep-char '\')
	     ;;
	     ;; ispell4:
	     ;;
	     (autoload 'ispell-word "ispell4"
	       "Check spelling of word at or before point" t)
	     (autoload 'ispell-complete-word "ispell4"
	       "Complete word at or before point" t)
	     (autoload 'ispell-region "ispell4"
	       "Check spelling of every word in the region" t)
	     (autoload 'ispell-buffer "ispell4"
	       "Check spelling of every word in the buffer" t)
	     (setq ispell-command "c:/progra~1/ispell4/exe/ispell.exe"
		   ispell-look-dictionary "c:/progra~1/ispell4/ispell.words"
		   ispell-look-command "c:/progra~1/ispell4/exe/look.exe"
		   ispell-command-options
		   (list "-d" "c:/progra~1/ispell4/ispell.dict")
		   )

	     ;; To run Cygnus bash under emacs:
	     ;;
	     (defun my-shell-setup ()
	       "For bash (cygwin 18) under Emacs 20"
	       (setq comint-scroll-show-maximum-output 'this)
	       (setq comint-completion-addsuffix t)
	       (setq comint-eol-on-send t)
	       (setq w32-quote-process-args ?\")
	       (make-variable-buffer-local 'comint-completion-addsuffix))

	     (setq shell-mode-hook 'my-shell-setup)
	     (setq process-coding-system-alist
		   (cons '("bash" . raw-text-unix)
			 process-coding-system-alist))

	     ;; Setup for shell from Jon Payne
	     ;; (http://www.cs.washington.edu/homes/voelker/ntemacs/discuss/bash-setup)
	     ;;
	     (setq shell-file-name "bash")
	     (setq explicit-shell-file-name shell-file-name)
	     (setq explicit-sh-args '("-login" "-i"))
	     (setq shell-command-switch "-c")
	     (setq archive-zip-use-pkzip nil)
	     (setenv "SHELL" shell-file-name)
	     (setq win32-quote-process-args t)
	     (setq win32-enable-italics t)
	     (setq comint-process-echoes nil)
	     (set-default-font "-*-Courier-New-normal-r-*-*-13-97-*-*-c-*-*-ansi-")
	     ;(menu-bar-mode 0)

	     ))
       ))

(defun review-mode ()
  (interactive)
  (text-mode)
  (auto-fill-mode)
  (setq major-mode 'review-mode mode-name "Review")
  (hilit-rehighlight-buffer))




(put 'eval-expression 'disabled nil)	; Allow ESC-ESC
(put 'narrow-to-region 'disabled nil)	; Allow narrow-to-region
(setq inhibit-startup-message t)	; No startup messages
(setq search-delete-char ?\^h)		; Delete character in i-search
(setq shell-prompt-pattern "^[^#$%>})]*[#$%>})] *") ; Include }-brace
(setq shell-completion-execonly nil)
(setq comint-input-autoexpand nil)

(setq vc-make-backup-files t)

(set-default 'mode-line-format '(" "
				 mode-line-buffer-identification
				 "%1*%1*   %[("
				 mode-name
				 minor-mode-alist
				 "%n"
				 mode-line-process
				 ")%]    "
				 (-3 . "%p")
				 "    "
				 global-mode-string))

(set-default 'mode-line-buffer-identification '("%b")) ; Change "Emacs: ..."


(if (and (getenv "TERM")
	 (not (string-match "xterm" (getenv "TERM"))))
    (display-time))			; Display time

(if (file-exists-p "~/.abbrev_defs")
    (quietly-read-abbrev-file "~/.abbrev_defs"))

(if (file-exists-p "~/.emacs_local")
    (load "~/.emacs_local"))

(cd (getenv "HOME"))
