<?php // AT Commerce ?>
<div id="page-wrapper"><div id="page">

  <?php if($page['draw']): ?>
    <div id="draw-wrapper">
      <div class="container clearfix">
        <div id="draw"><?php print render($page['draw']); ?></div>
      </div> 
    </div>
  <?php endif; ?>

  <div id="header-wrapper">
    <?php if($page['draw']): ?>
      <div id="toggle-wrapper">
        <div class="container clearfix">
           <div id="toggle"><?php print $draw_link; ?></div>
        </div>
      </div>
    <?php endif; ?>

    <div class="container clearfix">
      <header class="clearfix">

        <div id="branding" class="clearfix<?php print $branding_classes ? ' ' . $branding_classes : ''; ?>">
          <?php if ($linked_site_logo): ?>
            <div id="logo"><?php print $linked_site_logo; ?></div>
          <?php endif; ?>

          <?php if ($site_name || $site_slogan): ?>
            <hgroup<?php if (!$site_slogan && $hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>>
              <?php if ($site_name): ?>
                <h1 id="site-name"<?php if ($hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>><?php print $site_name; ?></h1>
              <?php endif; ?>
              <?php if ($site_slogan): ?>
                <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
              <?php endif; ?>
            </hgroup>
          <?php endif; ?>
        </div>

        <?php print render($page['header']); ?>

        <?php if ($page['menu_bar']): ?>
          <div id="nav-wrapper"><?php print render($page['menu_bar']); ?></div>
        <?php endif; ?>

      </header>
    </div>
  </div>

  <?php if ($page['secondary_content']): ?>
    <div id="secondary-content-wrapper"><div class="texture-overlay">
      <div class="container clearfix">
        <?php print render($page['secondary_content']); ?>
      </div>
    </div></div>
  <?php endif; ?>

  <div id="content-wrapper" class="<?php print $page['secondary_content'] ? 'with-secondary' : 'no-secondary'; ?>"><div class="container">

    <?php if ($page['three_33_first'] || $page['three_33_second'] || $page['three_33_third']): ?>
      <div id="sub-panels-wrapper">
        <div class="three-3x33 gpanel clearfix">
          <?php print render($page['three_33_first']); ?>
          <?php print render($page['three_33_second']); ?>
          <?php print render($page['three_33_third']); ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($messages || $page['help']): ?>
      <div id="messages-help-wrapper" class="clearfix">
        <?php print $messages; ?>
        <?php print render($page['help']); ?>
      </div>
    <?php endif; ?>

    <?php if ($breadcrumb): ?>
      <section id="breadcrumb" class="clearfix">
        <?php print $breadcrumb; ?>
      </section>
    <?php endif; ?>

    <div id="columns"><div class="columns-inner clearfix">
      <div id="content-column"><div class="content-inner">

        <?php print render($page['highlighted']); ?>

        <?php if ($page['two_50_first'] || $page['two_50_second']): ?>
          <div class="two-50 gpanel clearfix">
            <?php print render($page['two_50_first']); ?>
            <?php print render($page['two_50_second']); ?>
          </div>
        <?php endif; ?>

        <?php $tag = $title ? 'section' : 'div'; ?>
        <<?php print $tag; ?> id="main-content">

          <?php print render($title_prefix); ?>
          <?php if ($title && !isset($node)): ?>
            <header>
              <h1 id="page-title"><?php print $title; ?></h1>
            </header>
          <?php endif; ?>
          <?php print render($title_suffix); ?>

          <?php if ($primary_local_tasks || $secondary_local_tasks || $action_links): ?>
            <div id="tasks" class="clearfix">
              <?php if ($primary_local_tasks): ?>
                <ul class="tabs primary clearfix"><?php print render($primary_local_tasks); ?></ul>
              <?php endif; ?>
              <?php if ($secondary_local_tasks): ?>
                <ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
              <?php endif; ?>
              <?php if ($action_links = render($action_links)): ?>
                <ul class="action-links clearfix"><?php print $action_links; ?></ul>
              <?php endif; ?>
            </div>
          <?php endif; ?>

          <div id="content"><?php print render($page['content']); ?></div>

        </<?php print $tag; ?>>

        <?php print render($page['content_aside']); ?>

      </div></div>

      <?php print render($page['sidebar_first']); ?>
      <?php print render($page['sidebar_second']); ?>

    </div></div>

    <?php if ($page['tertiary_content']): ?>
      <div id="tertiary-content-wrapper">
        <?php print render($page['tertiary_content']); ?>
      </div>
    <?php endif; ?>

  </div></div>

  <?php if ($page['five_first'] || $page['five_second'] || $page['five_third'] || $page['five_fourth'] || $page['five_fifth']): ?>
    <div id="quint-panels-wrapper"><div class="texture-overlay">
      <div class="container clearfix">
        <div class="five-5x20 gpanel clearfix">
          <?php print render($page['five_first']); ?>
          <?php print render($page['five_second']); ?>
          <?php print render($page['five_third']); ?>
          <?php print render($page['five_fourth']); ?>
          <?php print render($page['five_fifth']); ?>
        </div>
      </div>
    </div></div>
  <?php endif; ?>

  <div id="page-footer">
    <?php if ($page['four_first'] || $page['four_second'] || $page['four_third'] || $page['four_fourth']): ?>
      <div id="footer-panels-wrapper"><div class="container clearfix">
        <div class="four-4x25 gpanel clearfix">
          <?php print render($page['four_first']); ?>
          <?php print render($page['four_second']); ?>
          <?php print render($page['four_third']); ?>
          <?php print render($page['four_fourth']); ?>
        </div>
      </div></div>
    <?php endif; ?>

    <?php if ($page['footer']): ?>
      <div id="footer-wrapper"><div class="container clearfix">
        <footer class="clearfix">
          <?php print render($page['footer']); ?>
        </footer>
     </div></div>
    <?php endif; ?>
  </div>

</div></div>
